/* MemLib, a part of V0ID's Unnamed Cheat
* MemLib.h
* All Rights reserved to V0ID
*/
#ifndef MEMLIB_H
#define MEMLIB_H

#include <iostream>
#include <vector>

typedef struct
{
	unsigned long address;
	unsigned char backup[6];
} sHook; //Structure with hook address and backup

class MemLib
{
	private:
		std::vector<sHook*> hookList; 

		MemLib();
		MemLib( const MemLib & );
	public:
		~MemLib();
		static MemLib & GetInstance()
		{
			static MemLib memLib;
			return memLib;
		}
		void WriteMemory(unsigned long address, PBYTE bytes, int size);
		void WriteNOPs(unsigned long address, int bytes);
		bool ImportHook(unsigned long address, size_t sizeNewFunc, ...);
		bool RemoveHook(unsigned long oldAddr);
		bool IsAddressHooked(unsigned long address);
		unsigned int  GetAddressBackupIndex(unsigned long address);
		bool InjectDLL(unsigned long processID, const char* pathDLL);
		unsigned long StartExecutable(const char* pathEXE);
		void EnableDebugPrivileges();
		void WriteJMP(unsigned long address, unsigned long dest);
};

#endif //MEMLIB_H