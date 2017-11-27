#include "../../stdafx.h"

void ChatRPC::OnPlayerMessage(BitStream* userData, Packet* packet)
{
	/*RakString message;
	(*userData) >> message;
	printf("[chat]%s\n", message.C_String());*/

	for( playerListIter i=pM.playerList.begin(); i!=pM.playerList.end(); ++i )
		if( i->second->address != packet->systemAddress )
			SIGNAL("OnPlayerMessage", userData, LOW_PRIORITY, i->second->address);
};