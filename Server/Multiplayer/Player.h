#ifndef _PLAYER_H
#define _PLAYER_H
class Player
{
public:
	int id;
	float matrix[17];
	RakString name, instance;
	unsigned char color[3];
	SystemAddress address;

	Player(SystemAddress add, int _id);
	~Player();
};
#endif