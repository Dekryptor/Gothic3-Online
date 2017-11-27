// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		if(!HookDirectX())
			MessageBoxA(GetActiveWindow(), "Cannot hook D3D9", "G3MP.dll", MB_OK);
		HookBind::BindHooks();
		Game::SetWindowName("Gothic III Multiplayer");		
		break;	
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		UnHookDirectX();
		break;
	}
	return TRUE;
}

