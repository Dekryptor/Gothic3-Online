#include "../stdafx.h"

PlayerManager::PlayerManager()
{
	playerList.clear();
};

PlayerManager::~PlayerManager()
{
	//Hmm..
};

Player* PlayerManager::CreatePlayer(SystemAddress sa, int id)
{
	if( IsExist(sa) == false )
	{
		Player* player = new Player(sa, id);
		if( player )
		{
			playerList[sa] = player;
			return player;
		}
	}
	return NULL;
};

bool PlayerManager::DestroyPlayer(Player *player)
{
	if( player )
	{
		DestroyPlayerForAll(player);
		playerList.erase(player->address);
		delete player;
		return true;
	}
	return false;
};

bool PlayerManager::DestroyPlayer(SystemAddress address)
{
	return DestroyPlayer(Get(address));
};

void PlayerManager::DestroyPlayerForAll(Player* player)
{
	if( GetPlayersCount() > 1 )
	{
		BitStream stream;
		stream << player->id;
		for(playerListIter i = playerList.begin(); i != playerList.end(); ++i)
			if( i->second != player )
				SIGNAL("DestroyPlayer", &stream, LOW_PRIORITY, i->second->address);
	}
};

Player* PlayerManager::Get(int id)
{
	for(playerListIter i=playerList.begin(); i!=playerList.end(); ++i )
		if(i->second->id == id)
			return i->second;
	return NULL;
};

Player* PlayerManager::Get(SystemAddress sa)
{
	return playerList[sa];
};

bool PlayerManager::IsExist(SystemAddress sa)
{
	return Get(sa) ? true : false;
};

bool PlayerManager::IsNameExist(RakString name)
{
	for(playerListIter i=playerList.begin(); i!=playerList.end(); ++i)
		if(name.StrCmp(i->second->name) == 0)
			return true;
	return false;
};

void PlayerManager::CreatePlayerForPlayer(Player *p1, Player *p2)
{
	if( p1 && p2 )
	{
		BitStream stream;
		stream << p1->id;
		stream << p1->name;
		stream << p1->color;
		stream << p1->instance;
		stream << p1->matrix;
		SIGNAL("CreatePlayer", &stream, LOW_PRIORITY, p2->address);
	}
};

void PlayerManager::CreateAllForPlayer(Player *player)
{
	if( player )
		if( GetPlayersCount() > 0 )
			for(playerListIter i = playerList.begin(); i != playerList.end(); ++i)
				if( i->second != player )
					CreatePlayerForPlayer(i->second,player);
};

void PlayerManager::CreatePlayerForAll(Player *player)
{
	if( player )
		if( GetPlayersCount() > 0 )
			for(playerListIter i = playerList.begin(); i != playerList.end(); ++i)
				if( i->second != player )
					CreatePlayerForPlayer(player,i->second);
};