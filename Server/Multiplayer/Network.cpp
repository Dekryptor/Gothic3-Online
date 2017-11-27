#include "../stdafx.h"

Network::Network() : peer(RakPeerInterface::GetInstance()), rpc4(new RPC4)
{
	maxSlots = 0;
};

Network::~Network()
{
};

bool Network::InitializeAndStart(size_t maxConnections, unsigned short port)
{
	if( peer )
	{
		peer->GetLocalIP(0);
		size_t numOfAddr = peer->GetNumberOfAddresses();
		SocketDescriptor sd(port, NULL);
		if( peer->Startup(maxConnections, &sd, 1) == RAKNET_STARTED )
		{
			maxSlots = maxConnections;
			peer->AttachPlugin(rpc4);
			RegisterRPCFuncs();
			peer->SetIncomingPassword("SATIVEWASHERE", strlen("SATIVEWASHERE"));
			peer->SetMaximumIncomingConnections(maxConnections);
			return true;
		}
	}
	return false;
};

void Network::RegisterRPCFuncs()
{
	rpc4->RegisterSlot("OnPlayerMessage", ChatRPC::OnPlayerMessage, 0);
	rpc4->RegisterSlot("CreatePlayer", PlayerRPC::OnJoin, 0);
	rpc4->RegisterSlot("OnPlayerMatrix", PlayerRPC::OnMatrix, 0);
	rpc4->RegisterSlot("OnPlayerAnimation", PlayerRPC::OnAnim, 0);
	rpc4->RegisterSlot("OnPlayerStats", PlayerRPC::OnStats, 0);
	rpc4->RegisterSlot("OnPlayerEquippedItems", PlayerRPC::OnEquippedItems, 0);
	rpc4->RegisterSlot("OnPlayerCombatMode", PlayerRPC::OnCombatMode, 0);
	rpc4->RegisterSlot("OnPlayerHit", PlayerRPC::OnHit, 0);
};

void Network::ReceivePackets()
{
	for(Packet* packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
	{
		switch(packet->data[0])
		{
		case ID_NEW_INCOMING_CONNECTION: /*puts("Incoming connection");*/ break;
		case ID_CONNECTION_LOST: PlayerRPC::OnDisconnect(packet); break;
		case ID_DISCONNECTION_NOTIFICATION: PlayerRPC::OnDisconnect(packet); break;
		default:
			fprintf(log, "[RakNet] Unknown packet received! ID: %d\n", (int)packet->data[0]); break;
		}
	}
};