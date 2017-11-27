#include "..\stdafx.h"
#pragma warning(disable:4018)
LocalPlayer::LocalPlayer() : Player()
{
	isSpawned = true;
	isRespawn = false;
	timeBroadcastAll = 0;
	timeBroadcastMatrix = 0;
	timeBroadcastAnimation = 0;
	timeBroadcastStats = 0;
	timeBroadcastEquipItems = 0;
	timeBroadcastCombatMode = 0;
	timeBroadcastHit = 0;
	timeBroadcastPing = 0;
	timeRespawn = 0;
	timeCheckRespawn = 0;
};

LocalPlayer::~LocalPlayer()
{
};

void LocalPlayer::process()
{
	BroadcastPing();
	//if pM.GetPlayersCount() > 0
	if( timeBroadcastAll < Game::GetTicks() )
	{
		entity = Entity::GetPlayer().GetGameEntity();
		if( entity )
		{
			//DO NOT BROADCAST ANYTHING IF LAGGED CUZ OF BUFFER OVERFLOW
			if( !CheckConnectionProblems() )
			{
				BroadcastMatrix();
				BroadcastAnimation();
				BroadcastStats();
				BroadcastEquippedItems();
				BroadcastCombatMode();
				BroadcastHit();
			}
			CheckRespawn();
		}
	}
};

void LocalPlayer::CreateNetLocalPlayer()
{
	entity = Entity::GetPlayer().GetGameEntity();
	bCMatrix mat = Entity::GetPlayer().GetPose();
	Game::GetCompleteMatrix(mat, matrix);
	XML_PUSH_VARS("G3MP-config.xml");
	XML_PARAM(nick, "nick");
	name = nick;
	RakString rsName(nick);
	BitStream stream;
	stream << rsName;
	stream << matrix;
	SIGNAL("CreatePlayer", &stream, IMMEDIATE_PRIORITY, RELIABLE);
	//Wait 3s before broadcasting anything
	timeBroadcastAll = Game::GetTicks() + 3000;
	/*//ONLY FOR TEST1111111111
	int stack;
	Game::GiveItem(entity, stack, "Body_King");
	Game::GiveItem(entity, stack, "Body_KingGuard");
	Game::GiveItem(entity, stack, "Body_Nom_Elite_Outlaw");
	Game::GiveItem(entity, stack, "Body_Paladin");
	Game::GiveItem(entity, stack, "It_Staff_Scythe_01", 2);
	Game::GiveItem(entity, stack, "It_Staff_Spear_01");
	Game::GiveItem(entity, stack, "It_Staff_Druid_01");
	Game::GiveItem(entity, stack, "It_1H_Sword_01", 2);
	Game::GiveItem(entity, stack, "Mike_Shield");
	Game::GiveItem(entity, stack, "It_Shield_Wood_04");
	//END11111111111*/
};

void LocalPlayer::BroadcastMatrix()
{
	if( timeBroadcastMatrix < Game::GetTicks() )
	{
		bCMatrix mat = Entity::GetPlayer().GetPose();
		Game::GetCompleteMatrix(mat, matrix);
		BitStream s;
		s << matrix;
		SIGNAL("OnPlayerMatrix", &s, LOW_PRIORITY, UNRELIABLE);
		timeBroadcastMatrix = Game::GetTicks() + 100;
	}
};

void LocalPlayer::BroadcastAnimation()
{
	if( timeBroadcastAnimation < Game::GetTicks() )
	{
		gCNPC_PS* npc = dynamic_cast<gCNPC_PS*>(entity->GetPropertySet("gCNPC_PS"));
		if( npc )
		{
			static bCString animation; //Because BREAKPOINT_EXCEPTION
			animation = npc->GetCurrentMovementAni();
			animation.Replace("%", "%%");
			const char* aniChar = animation.GetText();
			if( aniChar != NULL )
			{
					lastAni = aniChar;
					//Fucked loop ani fix
					if( lastAni.find("Ambient_Loop") == -1 && lastAni.find("Ambient_Ambient") == -1 &&
						lastAni.find("HoldRight") == -1 )
					{
						RakString ani(aniChar);
						BitStream stream;
						stream << ani;
						SIGNAL("OnPlayerAnimation", &stream, MEDIUM_PRIORITY, RELIABLE_ORDERED);
					}
			}
		}
		timeBroadcastAnimation = Game::GetTicks() + 500;
	}
};

void LocalPlayer::BroadcastStats()
{
	if( timeBroadcastStats < Game::GetTicks() )
	{
		gCPlayerMemory_PS* playerMem = dynamic_cast<gCPlayerMemory_PS*>(entity->GetPropertySet("gCPlayerMemory_PS"));
		if( playerMem )
		{
			hp[0] = playerMem->GetValue("HP");
			hp[1] = playerMem->GetMaximum("HP");
			mp[0] = playerMem->GetValue("MP");
			mp[1] = playerMem->GetMaximum("MP");
			sp[0] = playerMem->GetValue("SP");
			sp[1] = playerMem->GetMaximum("SP");
			str = playerMem->GetValue("STR");
			dex = playerMem->GetValue("DEX");
			//Also, state sync
			gCScriptRoutine_PS* scriptRoutine = dynamic_cast<gCScriptRoutine_PS*>(entity->GetPropertySet("gCScriptRoutine_PS"));
			if( scriptRoutine )
			{
				const char* text = Game::GetRoutineTask(scriptRoutine).GetText();
				if( text )
					currentTask = text;
			}
			//End state sync
			RakString task = currentTask.c_str();

			BitStream stream;
			stream << hp;
			stream << mp;
			stream << sp;
			stream << str;
			stream << dex;
			stream << task;
			SIGNAL("OnPlayerStats", &stream, LOW_PRIORITY, RELIABLE);
		}
		timeBroadcastStats = Game::GetTicks() + 1500;
	}
};

void LocalPlayer::BroadcastEquippedItems()
{
	if( timeBroadcastEquipItems < Game::GetTicks() )
	{
		//TODO: Check is dead
		char buff[12][128];
		memset(buff, 0, 12*(sizeof(buff[0])));	//Clear item names buffer
		int iCount = 0;	//Number of items
		eCEntity* itemBackup[12]; //Backup for current stored items
		if( gCEntity::GetCombatMode(entity) == gECombatMode_Carry )
		{
			gCInventory_PS* inventory = dynamic_cast<gCInventory_PS*>(entity->GetPropertySet("gCInventory_PS"));
			if( inventory )
			{
				for( size_t i = 0; i < 800; ++i ) //Check 800 slots for equipped items
				{
					if( inventory->IsValidIndex(i) == true )
					{
						const gCInventoryStack* invStack = inventory->GetStack(i);
						if( invStack )
						{
							if( invStack->IsEquipped(entity) == true )
							{
								bCMatrix mat;
								eCEntity* item = inventory->DropStack(i, &mat);
								if( item )
								{
									//Store current item
									itemBackup[iCount] = item;
									sprintf(&buff[iCount][0], item->GetName().GetText());
									iCount++;
									//Because when we drop item, item's count is lower by 1
									i--;
								}
							}
						}
					}
				}
				for( size_t i = 0; i < iCount; ++i )
				{
					//Equip stored items
					inventory->EquipStack(inventory->InsertStack(itemBackup[i]));
				}
				if( iCount > 0 )
				{
					BitStream stream;
					stream << buff;
					SIGNAL("OnPlayerEquippedItems", &stream, LOW_PRIORITY, UNRELIABLE);
				}
				else	//No one is equipped
				{
					sprintf(&buff[0][0], "NULL");
					BitStream stream;
					stream << buff;
					SIGNAL("OnPlayerEquippedItems", &stream, LOW_PRIORITY, UNRELIABLE);
				}
			}
		}
		timeBroadcastEquipItems = Game::GetTicks() + 3500;
	}
};

void LocalPlayer::BroadcastCombatMode()
{
	if( timeBroadcastCombatMode < Game::GetTicks() )
	{
		eCEntity* weapon = reinterpret_cast<gCEntity*>(entity)->GetWeapon(true);
		BitStream s;
		if( weapon )
			s << RakString(weapon->GetName().GetText());
		else
			s << RakString("NULL");
		SIGNAL("OnPlayerCombatMode", &s, LOW_PRIORITY, UNRELIABLE);
		timeBroadcastCombatMode = Game::GetTicks() + 1000;
	}
};

void LocalPlayer::BroadcastPing()
{
	if( timeBroadcastPing < Game::GetTicks() )
	{
		net->GetPeer()->Ping(net->GetServerAddr());
		timeBroadcastPing = Game::GetTicks() + 5000;
	}
};

bool LocalPlayer::CheckConnectionProblems()
{
	if( net->GetPeer()->GetLastPing(net->GetServerAddr()) >= 500 )
	{
		eCWnd* wnd = eCWnd::GetDesktopWindow();
		if( wnd )
			wnd->Print(bCPoint(372, 620), "# Connection problems #", &bCByteAlphaColor(255, 0, 0, 255), winUnk1);
		if(inp.IsGameInputActive() == true)
			inp.SetGameInputActive(false);
		return true;
	}
	if(inp.IsGameInputActive() == false && chat.isInputVisible() == false)
		inp.SetGameInputActive(true);
	return false;
};

void LocalPlayer::BroadcastHit()
{
	if( timeBroadcastHit < Game::GetTicks() )
	{
		if( gCEntity::GetCombatMode(entity) != gECombatMode_Carry )
		{
			gCFocus_PS* focus = dynamic_cast<gCFocus_PS*>(entity->GetPropertySet("gCFocus_PS"));
			if( focus )
			{
				eCEntity* fEntity = focus->FindFocusEntity(false);
				if( fEntity )
				{
					if( entity != fEntity && (Entity(fEntity).IsCharacter() == true || Entity(fEntity).IsNPC() == true) )
					{
						Player* netPlayer = pM.Get(fEntity);
						if( netPlayer )
						{
							//Entity found
							gCPlayerMemory_PS* fMemory = dynamic_cast<gCPlayerMemory_PS*>(fEntity->GetPropertySet("gCPlayerMemory_PS"));
							if( fMemory )
							{
								if( fMemory->GetValue("HP") < netPlayer->hp[0] )
								{
									//HP is lower, probably player is hitted
									int minusHP = netPlayer->hp[0] - fMemory->GetValue("HP");
									netPlayer->hp[0] -= minusHP;
									BitStream stream;
									stream << netPlayer->id;
									stream << minusHP;
									SIGNAL("OnPlayerHit", &stream, LOW_PRIORITY, RELIABLE);

									timeBroadcastHit = Game::GetTicks() + 600;
								}
							}
						}
					}
				}
			}
		}
	}
};

void LocalPlayer::CheckRespawn()
{
	if( timeCheckRespawn < Game::GetTicks() )
	{
		if( isRespawn == true )
		{
			if( timeRespawn > 0 )
				timeRespawn -= 1000;
			else
			{
				Game::RespawnHero(); //Stand up ;)
				currentTask = "PS_Normal"; //Bugfix for auto coutdown after respawn
				isRespawn = false;
			}
		}
		else
		{
			if(currentTask.compare("ZS_Dead") == 0) //Is dead?
			{
				timeRespawn = 6000;
				isRespawn = true;
			}
		}
		timeCheckRespawn = Game::GetTicks() + 1000;
	}
	//Information about respawn
	if( isRespawn == true )
	{
		eCWnd* screen = eCWnd::GetDesktopWindow();
		if( screen )
		{
			char message[21];
			sprintf(message, "Respawn in: %d...", timeRespawn / 1000);
			screen->Print(bCPoint(850, 540), bCString(message), &bCByteAlphaColor(196, 255, 0, 255), winUnk1);
		}
	}
};