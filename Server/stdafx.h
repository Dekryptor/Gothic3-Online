// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _WINSOCKAPI_
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;
#include <stdio.h>
#include <tchar.h>

//RakNet
#include "../Shared/Network/RakNetIncludes.h"
//XML
#include "../Shared/XMLWrapper.h"
//Math
#include "../Shared/Arithmetics.h"
//RPC
#include "Multiplayer/RPC/ChatRPC.h"
#include "Multiplayer/RPC/PlayerRPC.h"
//Server items
#include "Multiplayer/Player.h"
#include "Multiplayer/PlayerManager.h"
#include "Multiplayer/Network.h"
#include "Multiplayer/Core.h"




// TODO: reference additional headers your program requires here
