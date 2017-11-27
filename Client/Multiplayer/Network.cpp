#include "..\stdafx.h"
Network::Network(): isInitialized(false), peer(RakPeerInterface::GetInstance()), rpc4(new RPC4), isConnected(false)
{
};

Network::~Network()
{
	Disconnect(false);
	//peer->Shutdown(300);
	//RakPeerInterface::DestroyInstance(peer);
};

bool Network::Initialize()
{
	if( peer )
	{
		SocketDescriptor sd;
		if( peer->Startup(1,&sd,1) == RAKNET_STARTED )
		{
			peer->AttachPlugin(rpc4);
			RegisterRPCFuncs();
			isInitialized = true;
			return true;
		}
	}
	return false;
};

bool Network::Connect(string address, unsigned short port)
{
	if( isInitialized == true )
	{
		if(peer->Connect(address.c_str(), port, "SATIVEWASHERE", strlen("SATIVEWASHERE")) == 0)
		{
			char buff[130];
			sprintf(&buff[0], "Connecting to server on %s:%d, please wait...", address.c_str(), (int)port);
			chat.addLine(string(buff), 192, 255, 0);
			return true;
		}
	}
	return false;
};

void Network::Disconnect(bool isForced) //For future purposes
{
	isConnected = false;
	pM.ForceDestroyAll();
	peer->CloseConnection(serverAddress,!isForced,0,IMMEDIATE_PRIORITY);
	Sleep(1000);
};

void Network::RegisterRPCFuncs()
{
	if( isInitialized == false )
	{
		rpc4->RegisterSlot("OnPlayerMessage", ChatRPC::OnPlayerMessage, 0);
		rpc4->RegisterSlot("CreatePlayer", PlayerRPC::CreatePlayer, 0);
		rpc4->RegisterSlot("DestroyPlayer", PlayerRPC::DestroyPlayer, 0);
		rpc4->RegisterSlot("OnPlayerMatrix", PlayerRPC::OnMatrix, 0);
		rpc4->RegisterSlot("OnPlayerAnimation", PlayerRPC::OnAnim, 0);
		rpc4->RegisterSlot("OnPlayerStats", PlayerRPC::OnStats, 0);
		rpc4->RegisterSlot("OnPlayerEquippedItems", PlayerRPC::OnEquippedItems, 0);
		rpc4->RegisterSlot("OnPlayerCombatMode", PlayerRPC::OnCombatMode, 0);
		rpc4->RegisterSlot("OnPlayerHit", PlayerRPC::OnHit, 0);
	}
};

void Network::SetServerAddress(SystemAddress sa)
{
	if( isInitialized == true && isConnected == false )
	{
		serverAddress = sa;
		isConnected = true;
	}
}

void Network::ReceivePackets()	//Call only if initialized
{
	for(Packet* packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
	{
		switch(packet->data[0])
		{	
		//Raknetowskie od polaczenia
		case ID_CONNECTION_REQUEST_ACCEPTED: chat.addLine("You're joined to game", 192, 255, 0); SetServerAddress(packet->systemAddress); lP.CreateNetLocalPlayer(); break;
		case ID_CONNECTION_LOST: chat.addLine("Connection lost", 255, 0, 0); Disconnect(true); break;
		case ID_DISCONNECTION_NOTIFICATION: chat.addLine("Disconnected!", 255, 0, 0); Disconnect(true); break;
		case ID_CONNECTION_ATTEMPT_FAILED: chat.addLine("Connection attempt failed", 255, 0, 0); break;
		case ID_CONNECTION_BANNED: chat.addLine("You are banned from this server! (Connection failed)", 255, 0, 0); break;
		case ID_INVALID_PASSWORD: chat.addLine("Incorrect G3MP version (Connection failed)", 255, 0, 0); break; 
		case ID_ALREADY_CONNECTED: chat.addLine("You are already connected, try more times", 255, 0, 0); break;
		case ID_NO_FREE_INCOMING_CONNECTIONS: chat.addLine("Server is full", 255, 0, 0); break;

		default:
			char buff[130];
			sprintf(&buff[0], "(RakNet) Unknown packet received! ID: %d", (int)packet->data[0]);
			chat.addLine(string(buff), 255, 0, 0);
			break;
		}
	}
};