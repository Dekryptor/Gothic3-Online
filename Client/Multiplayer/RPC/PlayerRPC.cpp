#include "..\..\stdafx.h"

void PlayerRPC::CreatePlayer(BitStream* stream, Packet* packet)
{
	int id;
	RakString name, instance;
	(*stream) >> id;
	Player* player = pM.CreatePlayer(id);
	if( player )
	{
		(*stream) >> name;
		player->name = name.C_String();
		(*stream) >> player->color;
		(*stream) >> instance;
		player->instance = instance.C_String();
		(*stream) >> player->matrix;
		//Debug text
		char buff[128];
		sprintf(&buff[0], "Player %s (ID: %d) has been created", name.C_String(), player->id);
		chat.addLine(buff, 0, 255, 0);
	}
	else
		chat.addLine("Error while creating player!", 255, 0, 0);
};

void PlayerRPC::DestroyPlayer(BitStream* stream, Packet* packet)
{
	int id;
	(*stream) >> id;
	//Debug text
	Player* p = pM.Get(id);
	if( p )
	{
		char buff[128];
		sprintf(&buff[0], "Player %s (ID: %d) has been destroyed", p->name.c_str(), id);
		chat.addLine(buff, 255, 0, 0);
		pM.AddToDestroyQueue(p);
	}
};

void PlayerRPC::OnMatrix(BitStream* stream, Packet* packet)
{
	int id;
	(*stream) >> id;
	Player* player = pM.Get(id);
	if( player )
	{
		(*stream) >> player->matrix;
		if( player->isSpawned == true )
		{
			if( player->entity )
			{
				bCMatrix mat = Game::GetDefaultMatrix(player->matrix);
				//Przeróbmy to tak ¿eby zmienia³o tylko rotacjê
				bCMatrix curMat = Entity(player->entity).GetPose();
				mat[12] = curMat[12];
				mat[13] = curMat[13];
				mat[14] = curMat[14];
				Entity(player->entity).MoveTo(mat);
			}
		}
	}
};

//LocalPlayerRPC?
void PlayerRPC::OnHit(BitStream* stream, Packet* packet)
{
	int minusHP;
	(*stream) >> minusHP;
	eCEntity* hero = Entity::GetPlayer().GetGameEntity();
	if( hero )
	{
		gCPlayerMemory_PS* pMem = dynamic_cast<gCPlayerMemory_PS*>(hero->GetPropertySet("gCPlayerMemory_PS"));
		if( pMem )
		{
			int health = pMem->GetValue("HP") - minusHP;
			if( health < 0 )
				health = 0;
			pMem->SetValue("HP", health);
			char msg[256];
			sprintf(msg, "Hit received! Current HP level is: %d", health);
			chat.addLine(msg, 255, 0, 0);
			if( health == 0 )
			{
				gCScriptRoutine_PS* scriptRoutine = dynamic_cast<gCScriptRoutine_PS*>(hero->GetPropertySet("gCScriptRoutine_PS"));
				if( scriptRoutine )
					scriptRoutine->SetCurrentTask("ZS_Unconscious");
			}
		}
	}
};
void PlayerRPC::OnAnim(BitStream* stream, Packet* packet)
{
	int id;
	(*stream) >> id;
	Player* player = pM.Get(id);
	if( player )
	{
		RakString ani;
		(*stream) >> ani;
		//Temporary fix for looping animations
		if( ani.Find("Begin") != -1 && player->lastAni.find("Begin") != -1 )
			return;
		player->lastAni = ani.C_String();
		if( player->isSpawned == true )
		{
			gCNPC_PS* psnpc = dynamic_cast<gCNPC_PS*>(player->entity->GetPropertySet("gCNPC_PS"));
			if( psnpc )
			{
				static bCString anim;
				anim = psnpc->GetCurrentMovementAni();
				//Smoother animations
				if( ani.StrCmp(anim.GetText()) == 0 )
					return;
			}
			Entity(player->entity).StartPlayAni(player->lastAni.c_str(),1,false,1.0f,false);
		}
	}
};

void PlayerRPC::OnStats(BitStream* data, Packet* packet)
{
	int id;
	(*data) >> id;
	Player* player = pM.Get(id);
	if( player )
	{
		RakString task;
		(*data) >> player->hp;
		(*data) >> player->mp;
		(*data) >> player->sp;
		(*data) >> player->str;
		(*data) >> player->dex;
		(*data) >> task;
		player->currentTask = task.C_String();
		if( player->isSpawned == true )
		{
			if( player->entity )
			{
				gCPlayerMemory_PS* mem = dynamic_cast<gCPlayerMemory_PS*>(player->entity->GetPropertySet("gCPlayerMemory_PS"));
				if( mem )
				{
					mem->SetValue("HP", player->hp[0]);
					mem->SetMaximum("HP", player->hp[1]);
					mem->SetValue("MP", player->mp[0]);
					mem->SetMaximum("MP", player->mp[1]);
					mem->SetValue("SP", player->sp[0]);
					mem->SetMaximum("SP", player->sp[1]);
					mem->SetValue("STR", player->str);
					mem->SetValue("DEX", player->dex);
				}
				gCScriptRoutine_PS* rt = dynamic_cast<gCScriptRoutine_PS*>(player->entity->GetPropertySet("gCScriptRoutine_PS"));
				if( rt )
				{
					const char* task = Game::GetRoutineTask(rt).GetText();
					if( task )
						if( strcmp(task, player->currentTask.c_str()) != 0 )
							rt->SetCurrentTask(player->currentTask.c_str());
				}
			}
		}
	}
};

void PlayerRPC::OnEquippedItems(BitStream* data, Packet* packet)
{
	int id;
	char buff[12][128];
	memset(buff, 0, 12*(sizeof(buff[0])));	//Clear item names buffer
	(*data) >> id;
	(*data) >> buff;
	Player* player = pM.Get(id);
	if( player )
	{
		for(size_t i = 0; i < 12; ++i)
			memcpy(player->equippedItems[i], buff[i], 128);
		if( player->isSpawned == true )
		{
			if( player->entity )
			{
				//TODO: Check is dead
				gCInventory_PS* inventory = dynamic_cast<gCInventory_PS*>(player->entity->GetPropertySet("gCInventory_PS"));
				if( inventory )
				{
					for( size_t i = 0; i < 833; ++i ) //Destroy all items
					{
						if( inventory->UnEquipStack(i) == true )
							inventory->DeleteStack(i);
					}
					for( size_t i = 0; i < 12; ++i )
					{
						if( strlen(&buff[i][0]) > 2 )
						{
							int stack;
							if( Game::GiveItem(player->entity, stack, &buff[i][0]) != NULL )
								inventory->EquipStack(stack);
						}
					}
				}
			}
		}
	}
};

void PlayerRPC::OnCombatMode(BitStream* data, Packet* packet)
{
	int id;
	RakString itemName;
	(*data) >> id;
	(*data) >> itemName;
	Player* player = pM.Get(id);
	if( player )
	{
		player->combatItem = itemName.C_String();
		if( player->isSpawned == true )
		{
			if( player->entity )
			{
				gCInventory_PS* inv = dynamic_cast<gCInventory_PS*>(player->entity->GetPropertySet("gCInventory_PS"));
				if( inv )
				{
					eCEntity* weapon = reinterpret_cast<gCEntity*>(player->entity)->GetWeapon(true);
					if( weapon )
					{
						if( itemName.StrCmp("NULL") == 0 )	//Ca³kowite usuniêcie broni i przerwanie skrypta
						{
							Entity(weapon).Kill();
							return;
						}
						if( itemName.StrCmp(weapon->GetName().GetText()) != 0 )
						{
							gCItem_PS* item = dynamic_cast<gCItem_PS*>(weapon->GetPropertySet("gCItem_PS"));
							if( item )
							{
								item->SetSlot((gESlot)0);
								item->SetAmount(0);
							}
							goto equip_new;
						}
					}
					else
					{
equip_new:
						int stack;
						if( Game::GiveItem(player->entity, stack, itemName.C_String()) )
						{
							inv->EquipStackToSlot(stack, (gESlot)1); //Equip as item hehe
						}
					}
				}
			}
		}
	}
};