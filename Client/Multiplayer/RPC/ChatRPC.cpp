#include "..\..\stdafx.h"

void ChatRPC::OnPlayerMessage(BitStream* data, Packet* packet)
{
	RakString message;
	(*data) >> message;
	chat.addLine(message.C_String(), 255, 255, 255);
};