// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>

int _tmain(int argc, _TCHAR* argv[])
{
	srand((size_t)time(0));
	core.StartServer();
	return 0;
}

