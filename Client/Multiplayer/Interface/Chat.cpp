#include "..\..\stdafx.h"
#include <vector>
#include <string>
#pragma warning(disable:4244)
using namespace std;
Chat::Chat()
{
	maxLines = 13;
	cursorPos = 0;
	inputOpened = false;
	visible = true;
	chatLines.clear();
	inputText.clear();
	
};

Chat::~Chat()
{
	visible = false;
	inputOpened = false;
	chatLines.clear();
	inputText.clear();
};

void Chat::addLine(string text, unsigned char r, unsigned char g, unsigned char b)
{
	if( text.length() < 255 && text.length() > 0 )
	{
		chatLine chatline;
		chatline.text = text;
		chatline.color[0] = r;
		chatline.color[1] = g;
		chatline.color[2] = b;
		chatline.color[3] = 0;
		if( chatLines.size() < maxLines )
		{
			chatLines.push_back(chatline);
		}
		else
		{
			chatLines.erase(chatLines.begin());
			chatLines.push_back(chatline);
		}
	}
};

void Chat::draw()
{
	if( isVisible() == true )
	{
		eCWnd* screen = eCWnd::GetDesktopWindow();
		if( screen )
		{
			int lineDistance = 0;
			for(size_t i = 0; i < chatLines.size(); ++i)
			{
				if( chatLines[i].text.empty() == false )
				{
					screen->Print(bCPoint(0,lineDistance), bCString(chatLines[i].text.c_str()), &bCByteAlphaColor(chatLines[i].color[0], chatLines[i].color[1], chatLines[i].color[2], chatLines[i].color[3]), winUnk1);
					lineDistance += 15;
					//Draw smooth alpha
					if( chatLines[i].color[3] < 255 )
						chatLines[i].color[3] = GetLerp(chatLines[i].color[3], 255, 0.2f);
				}
			}
		}
	}
	this->drawInput();
};

void Chat::showInput(bool enable)
{
	if( enable == true )
	{
		inp.SetGameInputActive(false);
		inputOpened = true;
	}
	else
	{
		inp.SetGameInputActive(true);
		inputOpened = false;
	}
};

void Chat::drawInput()
{
	if( isInputVisible() == true )
	{
		int y = 15*(maxLines+1);
		eCWnd* screen = eCWnd::GetDesktopWindow();
		if( screen )
		{
			string tmpString = inputText;
			tmpString.insert(cursorPos, "_");
			tmpString.insert(0, "--> ");
			screen->Print(bCPoint(0,y), tmpString.c_str(), &bCByteAlphaColor(255,255,255,255), winUnk1);
		}
		static int timerBackspace = 0;
		if(timerBackspace < Game::GetTicks() )
		{
			if(inp.KeyPressed(VK_BACK))
			{
				if( inputText.length() > 0 && cursorPos > 0 )
				{
					inputText.erase(cursorPos-1, 1);
					cursorPos--;
					timerBackspace = Game::GetTicks() + 120;
				}
			}
			else if(inp.KeyPressed(VK_RETURN))
			{
				//Send chat message
				showInput(false);
				if(inputText.length() > 0)
				{
					if(net->IsConnected() == true )
					{
						RakString message("%s: %s", lP.name.c_str(), inputText.c_str());
						BitStream stream;
						stream << message;
						SIGNAL("OnPlayerMessage", &stream, LOW_PRIORITY, RELIABLE);
						addLine(message.C_String(), 255, 255, 255);
						inputText.clear();
						cursorPos = 0;
					}
				}
			}
			else if(inp.KeyPressed(VK_ESCAPE))
			{
				showInput(false);
			}
			else if(inp.KeyPressed(VK_LEFT))
			{
				if(cursorPos > 0)
					cursorPos--;
				timerBackspace = Game::GetTicks() + 120;
			}
			else if(inp.KeyPressed(VK_RIGHT))
			{
				if(cursorPos < inputText.length())
					cursorPos++;
				timerBackspace = Game::GetTicks() + 120;
			}
		}
	}
};

void Chat::onChar(char* symbol)
{
	if( isInputVisible() == true )
	{
		if(symbol)
		{
			if(inputText.size()>0)
				inputText.insert(cursorPos, symbol);
			else
				inputText = symbol;
			cursorPos++;
		}
	}
};