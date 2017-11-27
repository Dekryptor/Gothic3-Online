#ifndef _PLAYERRPC_H
#define _PLAYERRPC_H
namespace PlayerRPC
{
	void CreatePlayer(BitStream* data, Packet* packet);
	void DestroyPlayer(BitStream* data, Packet* packet);
	void OnMatrix(BitStream* data, Packet* packet);
	void OnAnim(BitStream* data, Packet* packet);
	void OnStats(BitStream* data, Packet* packet);
	void OnEquippedItems(BitStream* data, Packet* packet);
	void OnCombatMode(BitStream* data, Packet* packet);
	void OnHit(BitStream* data, Packet* packet);
};
#endif