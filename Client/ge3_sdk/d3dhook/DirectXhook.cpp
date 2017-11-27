//Only for EndScene
#include "..\..\stdafx.h"
//End
#pragma comment(lib, "detours.lib")
#include <detours.h>
#include "DirectXhook.h"
IDirect3DDevice9* pDevice = NULL;
eCDX9Device* geDevice = NULL;
PBYTE orig_eCDX9Device = NULL;
PBYTE orig_EndScene = NULL;
PBYTE orig_RenderDraw = NULL;
PBYTE orig_Release = NULL;

void EndScene();
void RenderDraw();

__declspec( naked ) void hook_eCDX9Device()
{
	__asm MOV geDevice, ECX
	__asm MOV EAX, [ESP+4]
	__asm MOV pDevice, EAX
	__asm JMP orig_eCDX9Device
};

__declspec( naked ) void hook_EndScene()
{
	__asm PUSHAD
		EndScene();
	__asm POPAD
	__asm JMP orig_EndScene
};

__declspec( naked ) void hook_RenderDraw()
{
	__asm PUSHAD
		RenderDraw();
	__asm POPAD
	__asm JMP orig_RenderDraw
};

__declspec( naked ) void hook_Release()
{
	__asm JMP orig_Release
};

bool HookDirectX()
{
	orig_eCDX9Device = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Engine.dll"), "??0eCDX9Device@@IAE@PAUIDirect3DDevice9@@@Z"), (PBYTE)&hook_eCDX9Device);
	orig_EndScene = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Engine.dll"), "?EndScene@eCDX9Device@@UAE?AW4bEResult@@XZ"), (PBYTE)&hook_EndScene);
	orig_RenderDraw = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Engine.dll"), "?OnRenderDraw@eCApplication@@MAEXXZ"), (PBYTE)&hook_RenderDraw);
	orig_Release = DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("Engine.dll"), "?OnLostDevice@eCDX9Font@@IAE?AW4bEResult@@XZ"), (PBYTE)&hook_Release);
	if(!orig_eCDX9Device)
		MessageBoxA(GetActiveWindow(), "!orig_eCDX9Device", "G3MP.dll", MB_OK);
	if(!orig_EndScene)
		MessageBoxA(GetActiveWindow(), "!orig_EndScene", "G3MP.dll", MB_OK);
	if(!orig_Release)
		MessageBoxA(GetActiveWindow(), "!orig_Release", "G3MP.dll", MB_OK);
	if( orig_eCDX9Device && orig_EndScene && orig_RenderDraw && orig_Release )
		return true;
	else return false;
};

void UnHookDirectX()
{
	//NULL
};

void EndScene()	//Callback
{
	
};

void RenderDraw()
{
	core.Process();
};