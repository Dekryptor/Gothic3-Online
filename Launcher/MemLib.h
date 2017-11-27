/* MemLib, a part of V0ID's Unnamed Cheat
* MemLib.h
* All Rights reserved to V0ID
*/
#ifndef MEMLIB_H
#define MEMLIB_H
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
class MemLib;


typedef struct
{
	unsigned long address;
	unsigned char backup[6];
} sHook; //Structure with hook address and backup

class MemLib
{

	public:
		MemLib();
		~MemLib();
		void WriteMemory(unsigned long address, PBYTE bytes, int size);
		void WriteNOPs(unsigned long address, int bytes);
		bool InjectDLL(unsigned long processID, const char* pathDLL);
		unsigned long StartExecutable(const char* pathEXE);
		void EnableDebugPrivileges();
		void WriteJMP(unsigned long address, unsigned long dest);
};

#endif //MEMLIB_H