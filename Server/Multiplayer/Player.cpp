#include "../stdafx.h"
Player::Player(SystemAddress addr, int _id) : address(addr), id(_id), name("Unknown"), instance("PC_Hero")
{
	memset(matrix,0,17);
	memset(color,0,3);
	color[0] = Random(130,255);
	color[1] = Random(130,255);
	color[2] = Random(0,10);
};


Player::~Player()
{
	//Communicate about destroying player
};