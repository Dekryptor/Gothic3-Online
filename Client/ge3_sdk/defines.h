#ifndef _DEFINES_H
#define _DEFINES_H
#define DLLIMPORT __declspec( dllimport )
#define THREAD_LOCAL __declspec( thread )
#define DLLIMPORT_EXTC extern "C" DLLIMPORT
#define DLLIMPORT_DATA extern "C++" DLLIMPORT
#define STDCALL __stdcall
#define CDECL __cdecl
#define FASTCALL __fastcall
#define FORCE_DWORD 0x7FFFFFFFL
#endif