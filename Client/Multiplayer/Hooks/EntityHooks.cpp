#include "..\..\stdafx.h"

PBYTE EntityRenderer_DrawFocusNames = NULL;
PBYTE Camera_Render = NULL;
eCCameraBase* camBase = NULL;
bool IsFocusNetworkPlayer()
{
	eCEntity* hero = Entity::GetPlayer().GetGameEntity();
	if( hero )
	{
		gCFocus_PS* focusPS = dynamic_cast<gCFocus_PS*>(hero->GetPropertySet("gCFocus_PS"));
		if( focusPS )
		{
			eCEntity* focus = focusPS->FindFocusEntity(false);
			if( focus )
			{
				if( pM.Get(focus) != NULL )
					return true;
			}
		}
	}
	return false;
};
__declspec( naked ) void hook_DrawFocusNames()
{
	__asm PUSHAD
	if( IsFocusNetworkPlayer() == true )
	{
		__asm POPAD
		__asm RETN	//Hide all standard nicknames
	}
	else
	{
		__asm POPAD
		__asm JMP EntityRenderer_DrawFocusNames
	}
};
__declspec( naked ) void hook_Render()
{
	__asm MOV camBase, ECX
	__asm JMP Camera_Render

};
bool EntityHooks::InstallHook()
{
	Camera_Render = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Engine.dll"), "?Render@eCCameraBase@@QAEX_N0@Z"), (PBYTE)&hook_Render);
	EntityRenderer_DrawFocusNames = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Game.dll"),"?DrawFocusNames@gCGUIEntityRenderer@@QAE_NXZ"), (PBYTE)&hook_DrawFocusNames);
	if( EntityRenderer_DrawFocusNames && Camera_Render )
		return true;
	return false;
};