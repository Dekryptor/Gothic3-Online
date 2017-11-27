/* MemLib, a part of V0ID's Unnamed Cheat
* MemLib.cpp
* All Rights reserved to V0ID
*/
#include <windows.h>
#include <tlhelp32.h>
#include "MemLib.h"
#pragma warning(disable:4996)

MemLib* pMemLib = NULL; //Global pointer to MemLib

MemLib::MemLib()
{
	pMemLib = this; //Assign "this" to global pointer of MemLib
}

MemLib::~MemLib()
{
	for(unsigned int i = 0; this->hookList.size(); ++i)	//Remove hooks when is used delete "this"
	{
		if(this->hookList[i]->address != NULL && this->hookList[i]->backup != NULL)
		{
			this->RemoveHook(this->hookList[i]->address);
		}
	}
	pMemLib = NULL; //NULL "this" pointer
}

void MemLib::WriteNOPs(unsigned long address, int bytes)
{
	unsigned long oldProtBack; //Backup of VirtualProtect

	VirtualProtect((LPVOID)address, bytes, PAGE_EXECUTE_READWRITE, &oldProtBack); //Remove protection 4 address
	memset((LPVOID)address, 0x90, bytes); //Write bytes of NOP (0x90 - NOP in x86)
	VirtualProtect((LPVOID)address, bytes, oldProtBack, &oldProtBack); //Restore old protection
}

void MemLib::WriteMemory(unsigned long address, PBYTE bytes, int size)
{
	unsigned long oldProtBack; //Backup of VirtualProtect

	VirtualProtect((LPVOID)address, size, PAGE_EXECUTE_READWRITE, &oldProtBack); //Remove protection at bytes of address
	memcpy((LPVOID)address, bytes, size); //Move array of bytes to address
	VirtualProtect((LPVOID)address, size, oldProtBack, &oldProtBack); //Restore old protection
}

unsigned int MemLib::GetAddressBackupIndex(unsigned long address)
{
	for(unsigned int i = 0; i < this->hookList.size(); ++i)
	{
		if(this->hookList[i]->address == address)
		{
			return i;
		}
	}
	return -1;
}

bool MemLib::IsAddressHooked(unsigned long address)
{
	for(unsigned int i = 0; i < this->hookList.size(); ++i) //Search for address in vector
	{
		if(this->hookList[i]->address == address)
		{
			return true; //Return true is addres found
		}
	}
	return false; //Else, return false
}

bool MemLib::ImportHook(unsigned long address, size_t sizeNewFunc, ...)
{
												//Disabled, because it's blocking some hooks
	if(this->IsAddressHooked(address) == false /*&& sizeNewFunc == sizeof(void*)*/) //Can't hook one address two or many times!
	{
		va_list args; //Serious, i don't understand va arguments, its taken from "CInject" from gothic multiplayer
		va_start(args, sizeNewFunc); //First arg is size of new function (?) stack?
		unsigned long function = (unsigned long)va_arg(args,void*); //Get function pointer from stack
		va_end(args); //End stack(WTF?!)

		sHook* newHook = (sHook*)malloc(sizeof(sHook)); //New member/whatever of structure
		newHook->address = address; //Assign address to this structure
	
		BYTE jmp[6] = { 0xE9, 0x00, 0x00, 0x00, 0x00, 0xC3 }; //asm JMP address
															  //asm RETN

		//Read address backup
		unsigned long oldProtBack;
		VirtualProtect((LPVOID)address, 6, PAGE_EXECUTE_READWRITE, &oldProtBack); //Remove protect
		memcpy(newHook->backup, (LPVOID)address, 6); //Write backup to newHook->backup
		VirtualProtect((LPVOID)address, 6, oldProtBack, &oldProtBack); //Restore protect

		unsigned long calcAddr = (function - address - 5); // new func - address of old func - 5
		memcpy(&jmp[1], &calcAddr, 4); //Move address to jump array
		
		this->hookList.push_back(newHook); //Add hook to list

		//Protection backup is up
		VirtualProtect((LPVOID)address, 6, PAGE_EXECUTE_READWRITE, &oldProtBack); //Remove protect
		memcpy((LPVOID)address, jmp, 6); //Write hook
		VirtualProtect((LPVOID)address, 6, oldProtBack, &oldProtBack); //Restore protect

		return true;

	}

	return false;
}

bool MemLib::RemoveHook(unsigned long address)
{
	if(this->IsAddressHooked(address) == true)
	{
			unsigned int backupIndex = this->GetAddressBackupIndex(address); //Get index of vect

			unsigned long oldProtBack; //Backup of old prot
			VirtualProtect((LPVOID)address, 6, PAGE_EXECUTE_READWRITE, &oldProtBack); //Rem prot
			memcpy((LPVOID)address, this->hookList[backupIndex]->backup, 6); //Write backup
			VirtualProtect((LPVOID)address, 6, oldProtBack, &oldProtBack); //Add prot

			//Free memory after malloc
			free(this->hookList.at(backupIndex));
			//Remove hook from list
			this->hookList.erase(hookList.begin() + backupIndex);

			return true;
	}

	return false;
}

bool MemLib::InjectDLL(unsigned long processID, const char *pathDLL)
{
	if(processID)
	{
		FILE* pFile = fopen(pathDLL, "r+");

		if(pFile)
		{
			fclose(pFile);

			LPVOID hKernel;
			LPVOID hDLL;

			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processID);

			if(hProcess)
			{
				hKernel = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"),"LoadLibraryA");
				hDLL = VirtualAllocEx(hProcess, NULL, strlen(pathDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

				WriteProcessMemory(hProcess, (LPVOID)hDLL, pathDLL, strlen(pathDLL), NULL);
				CreateRemoteThread(hProcess,NULL,NULL,(LPTHREAD_START_ROUTINE)hKernel,(LPVOID)hDLL,NULL,NULL);
				CloseHandle(hProcess);

				return true;
			}

			return false;
		}

		return false;
	}

	return false;
}

unsigned long MemLib::StartExecutable(const char* pathEXE)
{
	STARTUPINFO startInfo;
	PROCESS_INFORMATION procInfo;

	memset(&startInfo, 0, sizeof(startInfo));

	startInfo.cb = sizeof(startInfo);

	if(CreateProcess(pathEXE, NULL, NULL, NULL, false, NULL, NULL, NULL, &startInfo, &procInfo))
		return procInfo.dwProcessId;

	return 0;
}

void MemLib::EnableDebugPrivileges()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if ( ! OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
		return;
	if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) ){
		CloseHandle( hToken );
		return;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if ( ! AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
		CloseHandle( hToken );
}

void MemLib::WriteJMP(unsigned long address, unsigned long dest)
{
	unsigned char buff[5];

	*(unsigned char*)buff = 0xE9;
	*(unsigned long*)(buff + 1) = dest - address - 5;

	WriteMemory(address, buff, 5);
}