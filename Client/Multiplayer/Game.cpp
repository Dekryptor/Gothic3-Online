#include "..\stdafx.h"
#include <tchar.h>

extern eCCameraBase* camBase;

void Game::SetWindowName(const char* text)
{
	TCHAR windowName[128];
	_stprintf(windowName, _T(text));
	SetWindowText(GetForegroundWindow(), windowName);
};

void Game::DoubleClick(int x, int y)
{
	RECT rect;
	GetWindowRect(GetForegroundWindow(), &rect);
	x = rect.left + x;
	y = rect.top + y;

    const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * XSCALEFACTOR;
    double cy = cursorPos.y * YSCALEFACTOR;

    double nx = x * XSCALEFACTOR;
    double ny = y * YSCALEFACTOR;

    INPUT Input={0};
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)nx;
    Input.mi.dy = (LONG)ny;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

    SendInput(1,&Input,sizeof(INPUT));
    SendInput(1,&Input,sizeof(INPUT));

    Input.mi.dx = (LONG)cx;
    Input.mi.dy = (LONG)cy;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1,&Input,sizeof(INPUT));
}
int Game::GetTicks()
{
	return (int)GetTickCount();
};

void Game::ForceDisableTestmode()
{
	gCSession session = gCSession::GetSession();
	if( &session )
		if( session.IsInTestMode() == true )
			session.SetTestMode(false);
};

void Game::GetCompleteMatrix(bCMatrix mat, float (&completeMat)[17])
{
	for( size_t i = 0; i < 16; ++i )
		completeMat[i] = mat[i];
};

bCMatrix Game::GetDefaultMatrix(float (&completeMat)[17])
{
	bCMatrix mat;
	for( size_t i = 0; i < 16; ++i )
		mat[i] = completeMat[i];
	return mat;
};

eCEntity* Game::GiveItem(eCEntity* player, int& stackResult, bCString itemName, unsigned long amount)
{
	if( player )
	{
		bCVector pos = Entity(player).GetPosition();
		gCSession ses = gCSession::GetSession();
		eCEntity* item = ses.SpawnEntity(itemName, pos, true);
		if( item )
		{
			if( Entity(item).IsItem() == true )
			{
				gCInventory_PS* inv = dynamic_cast<gCInventory_PS*>(player->GetPropertySet("gCInventory_PS"));
				if( inv )
				{
					gCItem_PS* psitem = dynamic_cast<gCItem_PS*>(item->GetPropertySet("gCItem_PS"));
					if( psitem )
					{
						psitem->SetAmount(amount);
						stackResult = inv->InsertStack(item);
						return item;
					}
				}
			}
			Entity(item).Kill(); //Remove item from map
		}
	}
	return NULL;
};

void Game::RepairNicknames()
{
	if( camBase )
	{
		eCEntity* hero = Entity::GetPlayer().GetGameEntity();
		if( hero )
		{
			gCFocus_PS* focus = dynamic_cast<gCFocus_PS*>(hero->GetPropertySet("gCFocus_PS"));
			if( focus )
			{
				eCEntity* focusEntity = focus->FindFocusEntity(false);
				if( focusEntity )
				{
					bCVector pos = Entity(focusEntity).GetPosition();
					camBase->WorldToScreen(pos);
					eCWnd* window = eCWnd::GetDesktopWindow();
					if( window )
					{
						static bCString nickname = "Invaild";
						nickname.Clear();
						Player* networkPlayer = pM.Get(focusEntity);
						if( networkPlayer )
						{
							nickname = networkPlayer->name.c_str();
							window->Print(bCPoint(pos.m_fX,pos.m_fY/2),nickname,&bCByteAlphaColor(networkPlayer->color[0], networkPlayer->color[1], networkPlayer->color[2], 255),winUnk2);
						}
					}
				}
			}
		}
	}
};

void Game::RespawnHero()
{
	eCEntity* hero = Entity::GetPlayer().GetGameEntity();
	if( hero )
	{
		gCScriptRoutine_PS* scriptRoutine = dynamic_cast<gCScriptRoutine_PS*>(hero->GetPropertySet("gCScriptRoutine_PS"));
		if( scriptRoutine )
		{
			CompleteHeal(hero);
			scriptRoutine->SetCurrentTask("PS_Normal"); //Set state to normal
			Entity(hero).StopPlayAni();
		}
	}
};

const bCString Game::GetRoutineTask(gCScriptRoutine_PS* pThis) //Is unconscious?! DEAD?! HE IS SITTING?!!! 
{								//0x18 - GetCurrentTask			//This is answer for your questions ;)
	return (*(bCString*)((unsigned long)pThis+0x18));
};

void Game::CompleteHeal(eCEntity* entity)
{
	if( entity )
	{
		gCPlayerMemory_PS* pMem = dynamic_cast<gCPlayerMemory_PS*>(entity->GetPropertySet("gCPlayerMemory_PS"));
		if( pMem )
			pMem->SetValue("HP", pMem->GetMaximum("HP"));
	}
};