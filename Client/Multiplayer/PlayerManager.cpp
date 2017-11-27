#include "..\stdafx.h"

PlayerManager::PlayerManager()
{
	playerList.clear();
	destroyQueue.clear();
	timeDestroyQueue = 0;
};
PlayerManager::~PlayerManager()
{
};

Player* PlayerManager::Get(eCEntity *entity)
{
	if( entity )
	{
		for(playerListIter i=playerList.begin(); i!=playerList.end(); ++i)
		{
			if( i->second->entity == entity )
				return i->second;
		}
			
	}
	return NULL;
};

Player* PlayerManager::CreatePlayer(int id)
{		//Is exist?
	if( playerList[id] == NULL )
	{
		Player* player = new Player();
		if( player )
		{
			player->id = id;
			playerList[id] = player;
			return player;
		}
	}
	return NULL;
};

bool PlayerManager::DestroyPlayer(Player *player)
{
	if( player )
	{
		playerList.erase(player->id);
		delete player;
		return true;
	}
	return false;
};

Player* PlayerManager::Get(int id)
{
	return playerList[id];
};

bool PlayerManager::DestroyPlayer(int id)
{
	Player* player = Get(id);
	return DestroyPlayer(player);
};

void PlayerManager::ForceDestroyAll()
{
	if( GetPlayersCount() > 0 )
	{
		for(playerListIter i = playerList.begin(); i != playerList.end(); ++i )
			delete i->second;
		playerList.clear();
	}
};

void PlayerManager::ForceUnspawnAll()
{
	if( GetPlayersCount() > 0 )
	{
		for( playerListIter i = playerList.begin(); i != playerList.end(); ++i )
			if( i->second->isSpawned == true )
				i->second->Unspawn();
	}

};

void PlayerManager::Pulse()
{
	//Timed destroy player
	if( timeDestroyQueue < Game::GetTicks() )
	{
		eCEntity* hero = Entity::GetPlayer().GetGameEntity();
		eCEntity* focusEntity = NULL;
		if( hero )
		{
			gCFocus_PS* focus = dynamic_cast<gCFocus_PS*>(hero->GetPropertySet("gCFocus_PS"));
			if( focus )
				focusEntity = focus->FindFocusEntity(false);
		}
		for(size_t i = 0; i < destroyQueue.size(); ++i)
		{
			Player* p = destroyQueue.at(i);
			if( p != NULL )
			{
				if( (focusEntity == NULL) || (p->entity != focusEntity) )
				{
					destroyQueue.erase(destroyQueue.begin() + i);
					DestroyPlayer(p);
				}
			}
		}
		timeDestroyQueue = Game::GetTicks() + 500;
	}
	//Pulse all
	if( GetPlayersCount() > 0 )
	{
		for( playerListIter i = playerList.begin(); i != playerList.end(); ++i )
			i->second->Pulse();
	}
};

void PlayerManager::AddToDestroyQueue(Player *player)
{
	if( player )
	{
		destroyQueue.push_back(player);
		player->name += " (disconnected)";
		memset(player->color, 255, 3);
	}
};