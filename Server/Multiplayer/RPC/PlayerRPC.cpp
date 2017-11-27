#include "../../stdafx.h"

void PlayerRPC::OnJoin(BitStream* userData, Packet* packet)
{
	int id = (int)packet->systemAddress.systemIndex;
	if( id > -1 )
	{
		RakString name;
		(*userData) >> name;
		if( pM.IsNameExist(name) == true )
		{
			//REWRITE IT LATER, I SHOULD ADD SPECIAL MODULE FOR CREATING SPECYFIC PACKETS OR CALLING
			//SPECIAL CLIENT-SIDE FUNCTIONS FROM SERVER
			BitStream stream;
			stream << RakString("Nickname already exist");
			SIGNAL("OnPlayerMessage", &stream, HIGH_PRIORITY, packet->systemAddress);
			//CONNECTION WILL BE KILLED BECAUSE return IS NOT USED HERE
		}
		else
		{
			Player* player = pM.CreatePlayer(packet->systemAddress, (int)packet->systemAddress.systemIndex);
			if( player )
			{
				player->name = name;
				(*userData) >> player->matrix;
				//printf("Player %s created on pos %f %f %f\n", player->name.C_String(), player->matrix[12], player->matrix[13], player->matrix[14]);
				pM.CreatePlayerForAll(player);
				pM.CreateAllForPlayer(player);
				return;
			}
		}
	}
	net->GetPeer()->CloseConnection(packet->systemAddress, true, 0, LOW_PRIORITY);
};

void PlayerRPC::OnDisconnect(Packet* packet)
{
	//puts("Player disconnected");
	pM.DestroyPlayer(packet->systemAddress);
};


void PlayerRPC::OnAnim(BitStream* data, Packet* packet)
{
	Player* player = pM.Get(packet->systemAddress);
	if( player )
	{
		if( pM.GetPlayersCount() > 1 )
		{
			BitStream s;
			s << player->id;
			s << (*data);

			for( playerListIter i = pM.playerList.begin(); i != pM.playerList.end(); ++i )
				if( i->second != player )
					SIGNAL("OnPlayerAnimation", &s, MEDIUM_PRIORITY, i->second->address);
		}
	}
};

void PlayerRPC::OnMatrix(BitStream* data, Packet* packet)
{
	Player* player = pM.Get(packet->systemAddress);
	if( player )
	{
		(*data) >> player->matrix;
		BitStream s;
		s << player->id;
		s << player->matrix;

		if( pM.GetPlayersCount() > 1 )
			for( playerListIter i = pM.playerList.begin(); i != pM.playerList.end(); ++i )
				if( i->second != player )
					SIGNAL("OnPlayerMatrix", &s, MEDIUM_PRIORITY, i->second->address);
	}
};

void PlayerRPC::OnHit(BitStream* data, Packet* packet)
{
	int id;
	(*data) >> id;
	Player* player = pM.Get(id);
	if( player )
	{
		BitStream s;
		(*data) >> s; //HP
		SIGNAL("OnPlayerHit", &s, LOW_PRIORITY, player->address);
	}
};

void PlayerRPC::OnStats(BitStream* data, Packet* packet)
{
	Player* player = pM.Get(packet->systemAddress);
	if( player )
	{
		if( pM.GetPlayersCount() > 1 )
		{
			BitStream s;
			s << player->id;
			s << (*data);
			s << (*data);
			s << (*data);
			s << (*data);
			s << (*data);
			s << (*data);
			for( playerListIter i = pM.playerList.begin(); i != pM.playerList.end(); ++i )
				if( i->second != player )
					SIGNAL("OnPlayerStats", &s, LOW_PRIORITY, i->second->address);
		}
	}
};

void PlayerRPC::OnEquippedItems(BitStream* data, Packet* packet)
{
	Player* player = pM.Get(packet->systemAddress);
	if( player )
	{
		if( pM.GetPlayersCount() > 1 )
		{
			BitStream s;
			s << player->id;
			s << (*data);
			for( playerListIter i = pM.playerList.begin(); i != pM.playerList.end(); ++i )
				if( i->second != player )
					SIGNAL("OnPlayerEquippedItems", &s, LOW_PRIORITY, i->second->address);
		}
	}
};

void PlayerRPC::OnCombatMode(BitStream* data, Packet* packet)
{
	Player* player = pM.Get(packet->systemAddress);
	if( player )
	{
		if( pM.GetPlayersCount() > 1 )
		{
			BitStream s;
			s << player->id;
			s << (*data);
			
			for( playerListIter i = pM.playerList.begin(); i != pM.playerList.end(); ++i )
				if( i->second != player )
					SIGNAL("OnPlayerCombatMode", &s, LOW_PRIORITY, i->second->address);
		}
	}
};