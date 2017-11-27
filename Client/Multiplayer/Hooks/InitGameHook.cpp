#include "..\..\stdafx.h"

PBYTE gCSession_Start = NULL;

__declspec( naked ) void hook_gCS_Start() //Callback "onEnterWorld"
{
	__asm PUSHAD
		core.StartGame();
	__asm POPAD
	__asm JMP gCSession_Start
};

bool InitGameHook::InstallHook()
{
	gCSession_Start = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Game.dll"), "?Start@gCSession@@QAEXW4gESession_StartMode@@@Z"), (PBYTE)&hook_gCS_Start);
	if(gCSession_Start)
		return true;
	return false;
};