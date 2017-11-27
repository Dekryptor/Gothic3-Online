#include "..\..\stdafx.h"

void PlayerList::Render()
{
	static bool isVisible = false;
	if( inp.KeyPressed(VK_F1) )
	{
		if( isVisible == false )
		{
			chat.setVisible(false);
			isVisible = true;
		}
	}
	else if( !inp.KeyPressed(VK_F1) )
	{
		if( isVisible == true )
		{
			chat.setVisible(true);
			isVisible = false;
		}
	}
	if( isVisible == true )
	{
		eCWnd* screen = eCWnd::GetDesktopWindow();
		if( screen )
		{
			screen->Print(bCPoint(0, 0), bCString("ID:     Nickname:     Spawned:"), &bCByteAlphaColor(255, 230, 0, 255), winUnk1);
			long lineDist = 15;
			for( playerListIter i = pM.playerList.begin(); i != pM.playerList.end(); ++i )
			{
				char textFormat[128];
				sprintf(textFormat, "%d       %s             %s", i->second->id, i->second->name.c_str(), i->second->isSpawned ? "true" : "false");
				screen->Print(bCPoint(0, lineDist), bCString(textFormat), &bCByteAlphaColor(255, 255, 255, 255), winUnk1);
				lineDist += 15;
			}
		}
	}
};