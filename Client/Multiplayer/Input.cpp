#include "..\stdafx.h"
#include <Windowsx.h>
extern int timeHandleMessage;
Input::Input()
{
	isGameInputActive = true;
	keyBuffer = 0;
};

Input::~Input()
{

};

void Input::Process()
{
	int key = 0;
	byte keyState[256];
	GetKeyboardState(keyState);
	for( size_t i = 0x20; i < 0xFE; ++i )
	{
		if( KeyPressed(i) && 
			i != VK_RSHIFT && i != VK_LSHIFT )
		{
			char currentKey[32];
			if( ToAscii(i, MapVirtualKey(i,0), keyState, (LPWORD)currentKey, 0) )
			{
				key = currentKey[0];
				break;
			}
			else key = 0;
		}
	}
	static char lastKey = ' ';
	static int timeLastKey = 0;
	if( key != 0 )
	{
		if( lastKey != key )
		{
			lastKey = key;
			OnKeyInput(lastKey);
			timeLastKey = Game::GetTicks() + 180;
		}
		else
		{
			if(timeLastKey < Game::GetTicks() )
			{
				OnKeyInput(lastKey);
				timeLastKey = Game::GetTicks() + 180;
			}
		}
	}
};

char Input::GetLastChar()
{
	int key = keyBuffer;
	keyBuffer = 0;
	return key;
};

SHORT Input::KeyPressed(int vKey)
{
	return (GetAsyncKeyState(vKey) & 0x8000);
};

void Input::OnKeyInput(char Key)
{
	//Call to chat or whatever
	if( Key == 'Y' || Key == 'y' || GetAsyncKeyState(0x59) )
	{
		if( !chat.isInputVisible() )
		{
			chat.showInput(true);
			return;
		}
	}
	if( chat.isInputVisible() )
	{
		chat.onChar(&Key);
	}
};

void Input::SetGameInputActive(bool enable)
{
	isGameInputActive = enable;
	timeHandleMessage = Game::GetTicks() + 200; //Blokuje input in-game (wyskakiwanie okienek po zamknieciu czatu)
};