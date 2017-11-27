#ifndef _PLAYER_H
#define _PLAYER_H
class Player
{
public:
	int id;
	string name, instance, lastAni, combatItem, currentTask;
	char equippedItems[12][128];
	unsigned char color[3];
	float matrix[17];
	bool isSpawned;
	eCEntity* entity;
	//Statistics
	//x[0] - current value x[1] - maximum value
	int hp[2];
	int mp[2];
	int sp[2];
	int str;
	int dex;
public:
	Player();
	~Player();
	
	bool Spawn();
	bool Spawn(int _id, string _name, string _instance, float _x, float _y, float _z);
	void Respawn();
	void Unspawn();
	void Stream(); //Matrix of local player
	void Pulse();
private:
	void RefreshPosition();
	void RefreshDeath();
	void RefreshHealth();
	void RefreshCombat();
};
#endif