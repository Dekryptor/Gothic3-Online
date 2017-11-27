#ifndef _DIRECTXHOOK_H
#define _DIRECTXHOOK_H
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <d3dx9.h>
#include <d3d9.h>
class eCDX9Device;
bool HookDirectX();
void UnHookDirectX();
#endif