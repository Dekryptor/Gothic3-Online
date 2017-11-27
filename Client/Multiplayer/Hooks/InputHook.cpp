#include "..\..\stdafx.h"

PBYTE eCApplication_OnKeyboard = NULL;
PBYTE eCApplication_OnMouse = NULL;
PBYTE eCActionMapper_Process = NULL;
int timeHandleMessage = NULL;

bool isStarted(){ return core.IsStarted();};
void process(){ inp.Process();};
bool isGameInputActive(){ return inp.IsGameInputActive();};
__declspec( naked ) void hook_OnKeyboard()
{	__asm PUSHAD
	/*if( isStarted() == true )
	{
		process();
	}*/
	__asm POPAD
	__asm PUSHAD
	if( isGameInputActive() == true )
	{
		__asm POPAD
		__asm JMP eCApplication_OnKeyboard
	}
	__asm POPAD
	__asm RETN
};

__declspec( naked ) void hook_OnMouse()
{	
	__asm PUSHAD
	if( isGameInputActive() == true )
	{
		__asm POPAD
		__asm JMP eCApplication_OnMouse
	}
	__asm POPAD
	__asm RETN
};

__declspec( naked ) void hook_OnActionMapper()
{
	__asm PUSHAD
	if( timeHandleMessage < Game::GetTicks() )
	{
		__asm POPAD
		__asm JMP eCActionMapper_Process
	}
	__asm POPAD
	__asm RETN
};

bool InputHook::InstallHook()
{
	eCApplication_OnKeyboard = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Engine.dll"), "?OnKeyboard@eCApplication@@MAEXXZ"), (PBYTE)&hook_OnKeyboard);
	eCApplication_OnMouse = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Engine.dll"), "?OnMouse@eCApplication@@MAEXXZ"), (PBYTE)&hook_OnMouse);
	eCActionMapper_Process = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Engine.dll"), "?Process@eCActionMapper@@UAEXXZ"), (PBYTE)&hook_OnActionMapper);
	if(eCApplication_OnKeyboard && eCApplication_OnMouse && eCActionMapper_Process)
		return true;
	return false;
};