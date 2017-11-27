#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H
#define pM PlayerManager::GetInstance()
#define playerListIter map<SystemAddress, Player*>::iterator
class PlayerManager
{
private:
	PlayerManager();
	PlayerManager( const PlayerManager & ) {};
	~PlayerManager();
	void DestroyPlayerForAll(Player* player);
	void CreatePlayerForPlayer(Player* p1, Player* p2);

public:
	static PlayerManager& GetInstance()
	{
		static PlayerManager singletone;
		return singletone;
	}
	map<SystemAddress, Player*> playerList;
	
	Player* CreatePlayer(SystemAddress sa, int id);
	bool DestroyPlayer(Player* player);
	bool DestroyPlayer(SystemAddress address);
	void CreatePlayerForAll(Player* player);
	void CreateAllForPlayer(Player* player);
	Player* Get(SystemAddress sa);
	Player* Get(int id);
	bool IsExist(SystemAddress sa);
	bool IsNameExist(RakString name);
	size_t GetPlayersCount() { return this->playerList.size();};
};
#endif