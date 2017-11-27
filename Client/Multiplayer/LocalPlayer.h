#ifndef _LOCALPLAYER_H
#define _LOCALPLAYER_H
#define lP LocalPlayer::GetInstance()
class LocalPlayer : public Player
{
private:
	LocalPlayer();
	LocalPlayer( const LocalPlayer & ) {};
	~LocalPlayer();

	size_t timeBroadcastAll;
	size_t timeBroadcastMatrix;
	size_t timeBroadcastAnimation;
	size_t timeBroadcastStats;
	size_t timeBroadcastEquipItems;
	size_t timeBroadcastCombatMode;
	size_t timeBroadcastPing;
	size_t timeBroadcastHit;
	size_t timeRespawn;
	size_t timeCheckRespawn; //For executing function every 1 sec
	bool isRespawn;
public:
	static LocalPlayer & GetInstance()
	{
		static LocalPlayer singletone;
		return singletone;
	}
	void process();
	void CreateNetLocalPlayer();
private:
	void BroadcastAnimation();
	void BroadcastMatrix();
	void BroadcastStats();
	void BroadcastEquippedItems();
	void BroadcastCombatMode();
	void BroadcastPing();
	void BroadcastHit();
	bool CheckConnectionProblems();
	void CheckRespawn();
	
};
#endif