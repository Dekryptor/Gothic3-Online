#include "..\..\stdafx.h"

void HookBind::BindHooks()
{
	if(!InitGameHook::InstallHook() || !InputHook::InstallHook() || !EntityHooks::InstallHook())
		MessageBoxA(GetActiveWindow(), "Cannot install one or more hooks", "G3MP.dll", MB_OK);
};