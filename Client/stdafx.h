// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _BIND_TO_CURRENT_VCLIBS_VERSION 1
#define _WINSOCKAPI_
#define _CRT_SECURE_NO_WARNINGS

#include "targetver.h"
#include "ge3_sdk/g3-sdk.h"
#include "ge3_sdk/d3dhook/DirectXHook.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
//It is included in raknet
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
#pragma comment(lib, "detours.lib")
#include <detours.h>
//Network
#include "..\Shared\Network\RakNetIncludes.h"
//Arithmetics
#include "..\Shared\Arithmetics.h"
//XML
#include "..\Shared\XMLWrapper.h"

#include "Multiplayer\Core.h"
#include "Multiplayer\Game.h"
#include "Multiplayer\Input.h"
#include "Multiplayer\Network.h"
#include "Multiplayer\Player.h"
#include "Multiplayer\PlayerManager.h"
#include "Multiplayer\LocalPlayer.h"
#include "Multiplayer\Interface\Chat.h"
#include "Multiplayer\Interface\PlayerList.h"
#include "Multiplayer\RPC\ChatRPC.h"
#include "Multiplayer\RPC\PlayerRPC.h"
#include "Multiplayer\Hooks\HookBind.h"
#include "Multiplayer\Hooks\InitGameHook.h"
#include "Multiplayer\Hooks\InputHook.h"
#include "Multiplayer\Hooks\EntityHooks.h"