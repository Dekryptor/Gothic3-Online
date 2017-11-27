#include "../stdafx.h"
Core::Core() : network(new Network())
{
	logFile = fopen("errlog.txt", "a");
	if(!logFile)
	{
		printf("[core] Cannot open log file for writing, aborting..");
		do{ Sleep(1000); }while(!getchar());
		exit(1);
	}
};

Core::~Core()
{
	if(logFile)
		fclose(logFile);
	delete network;
};

void Core::StartServer()
{
	//Hahaha, what i should do as next? XD
	//OK, i know, so, let's do this
	/*XML_PUSH_VARS("G3MP-config.xml");
	XML_PARAM(slots, "maxSlots");
	XML_PARAM(port, "port");*/
	if( network->InitializeAndStart(1000, 8888) == true )//Testing port
	{
		puts("G3-MP server is running.");
		do
		{
			//Receive packets
			network->ReceivePackets();
			Sleep(1);
		} while(true);
	}
	else
		fprintf(logFile,"[RakNet] Cannot start network!\n");
};