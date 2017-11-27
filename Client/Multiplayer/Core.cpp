#include "..\stdafx.h"

extern IDirect3DDevice9 *pDevice;
Core::Core() : isStarted(false), pNetwork(new Network())
{
	
};

Core::~Core()
{
	delete pNetwork;
};

void Core::StartGame()
{
	if( isStarted == false )
	{
		if(!pDevice)
			MessageBoxA(GetActiveWindow(), "D3DDEVICE9 NULL!", "G3MP.dll", MB_OK);
		gui2.PrintGameMessage("Gothic3 Multiplayer Pre-Alpha Update 3", TEXT_DARKGREEN);
		gui2.PrintGameMessage("It is in development version, so it has many bugs which will be fixed in future releases.", TEXT_DARKGREEN);
		gui2.PrintGameMessage("Thank you for testing ;)", TEXT_DARKGREEN);
	
		if( pNetwork->Initialize() == true )
		{
			XML_PUSH_VARS("G3MP-config.xml");
			XML_PARAM(ip, "ip");
			XML_PARAM(port, "port");

			//pNetwork->Connect("194.135.91.47", 8888);
			if( pNetwork->Connect(ip, atoi(port)) == false )
				chat.addLine("Cannot connect to server (socket error)", 255, 0, 0);
		}
		else chat.addLine("Cannot initialize network", 255, 0, 0);
		isStarted = true;
	}
};

void Core::Process()
{
	if( isStarted == true )
	{
		//Here it is faster
		inp.Process();
		//Render chat
		chat.draw();
		//Receive packets
		if( pNetwork->IsInitialized() )
		{
			pNetwork->ReceivePackets();
			PlayerList::Render();
		}
		//Process local player and repair
		if( pNetwork->IsConnected() )
		{
			lP.process();
			pM.Pulse();
			Game::RepairNicknames();
			//Temporary solution for crashing while saving
			if( gui2.IsMenuOpen() == true )
				pM.ForceUnspawnAll();
		}
		else if( inp.IsGameInputActive() == false && chat.isInputVisible() == false ) //FAST FIX, I SHOULD THINK MOAR ABOUT ENABLING GAME INPUT
			inp.SetGameInputActive(true);
	}
	//NONSENSE BUT IT'S ONLY TEMPORARY SOLUTION
	/*else //Force mouse click on "new game" option in menu
	{
		static size_t timeClick = Game::GetTicks();
		if( timeClick < Game::GetTicks() )
		{
			Game::DoubleClick(500, 390);
			Game::DoubleClick(440, 320);
			timeClick = Game::GetTicks() + 6000;
		}
	}*/
};