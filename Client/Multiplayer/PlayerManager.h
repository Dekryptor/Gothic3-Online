#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H
#define pM PlayerManager::GetInstance()
#define repair pM.GetRepair()
#define playerListIter map<int, Player*>::iterator

class Repair;
class PlayerManager
{
private:
	PlayerManager();
	PlayerManager( const PlayerManager & ) {};
	~PlayerManager();

	size_t timeDestroyQueue;
public:
	static PlayerManager& GetInstance()
	{
		static PlayerManager singletone;
		return singletone;
	}
	map<int, Player*> playerList;
	vector<Player*> destroyQueue;
	Player* CreatePlayer(int id);
	bool DestroyPlayer(Player* player);
	bool DestroyPlayer(int id);
	size_t GetPlayersCount() { return this->playerList.size();};
	Player* Get(eCEntity* entity);
	Player* Get(int id);
	void ForceDestroyAll();
	void ForceUnspawnAll();
	void Pulse();
	void AddToDestroyQueue(Player* player);
};
#endif