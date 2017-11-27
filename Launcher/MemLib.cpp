/* MemLib, a part of V0ID's Unnamed Cheat
* MemLib.cpp
* All Rights reserved to V0ID
*/

#include "MemLib.h"

#pragma comment(lib, "Advapi32.lib")
MemLib* pMemLib = NULL; //Global pointer to MemLib

MemLib::MemLib()
{
	pMemLib = this; //Assign "this" to global pointer of MemLib
}

MemLib::~MemLib()
{
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
                hKernel = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"),"LoadLibraryA");
				hDLL = VirtualAllocEx(hProcess, NULL, strlen(pathDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

				WriteProcessMemory(hProcess, (LPVOID)hDLL, pathDLL, strlen(pathDLL), NULL);
                CreateRemoteThread(hProcess,NULL,0,(LPTHREAD_START_ROUTINE)hKernel,(LPVOID)hDLL,0,NULL);
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
    STARTUPINFOA startInfo;
	PROCESS_INFORMATION procInfo;

	memset(&startInfo, 0, sizeof(startInfo));

	startInfo.cb = sizeof(startInfo);

    if(CreateProcessA(pathEXE, NULL, NULL, NULL, false, NULL, NULL, NULL, &startInfo, &procInfo))
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
