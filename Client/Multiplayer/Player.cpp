#include "..\stdafx.h"

Player::Player() : id(-1), name("Unknown"), instance("PC_Hero"), lastAni("NULL"), combatItem("NULL"), currentTask("PS_Normal"), entity(0), isSpawned(false)
{
	str = 0;
	dex = 0;
	memset(hp, 100, 2);
	memset(mp, 0, 2);
	memset(sp, 0, 2);
	memset(matrix, 0, 17);
	memset(color, 0, 3);
	memset(equippedItems, 0, 12*sizeof(equippedItems[0]));
};

Player::~Player()
{
	if( isSpawned == true )
		Unspawn();
};

bool Player::Spawn(int _id, string _name, string _instance, float _x, float _y, float _z)
{
	id = _id;
	name = _name;
	instance = _instance;
	matrix[12] = _x;
	matrix[13] = _y;
	matrix[14] = _z;
	return Spawn();
};

bool Player::Spawn()
{
	gCSession session = gCSession::GetSession();
	if( &session )
	{
		entity = session.SpawnEntity(instance.c_str(), bCVector(matrix[12],matrix[13],matrix[14]), true);
		if( entity )
		{
			gCCharacterMovement_PS* PScharMovement = dynamic_cast<gCCharacterMovement_PS*>(entity->GetPropertySet("gCCharacterMovement_PS"));
			if( PScharMovement )
			{
				PScharMovement->SetTurnAcceleration(0.0f);
				PScharMovement->SetTurnDecceleration(0.0f);
				PScharMovement->SetTurnSpeedMax(0.0f);
				PScharMovement->SetTurnSpeedModifier(0.0f);
			}
			//Restore "things"
			gCPlayerMemory_PS* mem = dynamic_cast<gCPlayerMemory_PS*>(entity->GetPropertySet("gCPlayerMemory_PS"));
			if( mem )
			{
				mem->SetValue("HP", hp[0]);
				mem->SetMaximum("HP", hp[1]);
				mem->SetValue("MP", mp[0]);
				mem->SetMaximum("MP", mp[1]);
				mem->SetValue("SP", sp[0]);
				mem->SetMaximum("SP", sp[1]);
				mem->SetValue("STR", str);
				mem->SetValue("DEX", dex);
			}
			//Wear items
			gCInventory_PS* inventory = dynamic_cast<gCInventory_PS*>(entity->GetPropertySet("gCInventory_PS"));
			if( inventory )
			{
				for( size_t i = 0; i < 833; ++i ) //Destroy all items
				{
					if( inventory->UnEquipStack(i) == true )
						inventory->DeleteStack(i);
				}
				for( size_t i = 0; i < 12; ++i )
				{
					if( strlen(&equippedItems[i][0]) > 2 )
					{
						int stack;
						if( Game::GiveItem(entity, stack, &equippedItems[i][0]) != NULL )
							inventory->EquipStack(stack);
					}
				}
			}
			//End wear items
			//Combat item
			gCInventory_PS* inv = dynamic_cast<gCInventory_PS*>(entity->GetPropertySet("gCInventory_PS"));
			if( inv )
			{
				eCEntity* weapon = reinterpret_cast<gCEntity*>(entity)->GetWeapon(true);
				if( weapon )
				{
					if( combatItem.compare("NULL") == 0 )
					{
						Entity(weapon).Kill();
					}
					else if( combatItem.compare(weapon->GetName().GetText()) != 0 )
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
					if( Game::GiveItem(entity, stack, combatItem.c_str()) )
					{
						inv->EquipStackToSlot(stack, (gESlot)1); //Equip as item hehe
					}
				}
			}
			//End combat item
			Entity(entity).StartPlayAni(lastAni.c_str(),1,false,1.0f,false);
			//Entity task
			gCScriptRoutine_PS* routine = dynamic_cast<gCScriptRoutine_PS*>(entity->GetPropertySet("gCScriptRoutine_PS"));
			if( routine )
				routine->SetCurrentTask(currentTask.c_str());
			//End of entity task
			isSpawned = true;
			return true;
		}
	}
	return false;
};

void Player::Unspawn()
{
	isSpawned = false;
	if( entity )
		Entity(entity).Kill();
		//entity->Enable(false);
	entity = NULL;
};

void Player::Respawn()
{
	if( isSpawned == true )
	{
		Unspawn();
		isSpawned = Spawn();
	}
};

void Player::Pulse()
{
	Stream();
	if( isSpawned == true )
	{
		RefreshPosition();
		RefreshDeath();
		RefreshHealth();
		RefreshCombat();
	}
};

void Player::RefreshPosition()
{
	if( entity )
	{
		bCMatrix curMat = Entity(entity).GetPose();
		float dist = GetDistance3D(curMat[12], curMat[13], curMat[14], matrix[12], matrix[13], matrix[14]);
		if( dist > 300 )
		{
			bCMatrix mat = Game::GetDefaultMatrix(matrix);
			Entity(entity).MoveTo(mat);
		}
		else if( dist > 5 )
		{
			bCVector pos(curMat[12], curMat[13], curMat[14]);
			bCMatrix mat = Game::GetDefaultMatrix(matrix);
			bCVector newPos = GetLerp(pos, bCVector(mat[12], mat[13], mat[14]), 0.18f);
			mat[12] = newPos.m_fX;
			mat[13] = newPos.m_fY;
			mat[14] = newPos.m_fZ;
			Entity(entity).MoveTo(mat);
		}
	}
};

void Player::RefreshDeath()
{
	if( entity )
	{
		if( Entity(entity).IsDead() == true && hp[0] > 0 )
			Respawn();
	}
};

void Player::RefreshHealth()
{
	if( entity )
	{
		gCPlayerMemory_PS* playerMem = dynamic_cast<gCPlayerMemory_PS*>(entity->GetPropertySet("gCPlayerMemory_PS"));
		if( playerMem )
			playerMem->SetValue("HP", hp[0]);
	}
};

void Player::RefreshCombat() //Because game is removing weapon, idk why
{
	if( entity )
	{	
		if( combatItem.compare("NULL") != 0 )
		{
			eCEntity* weapon = reinterpret_cast<gCEntity*>(entity)->GetWeapon(true);
			if( !weapon )
			{
				gCInventory_PS* inventory = dynamic_cast<gCInventory_PS*>(entity->GetPropertySet("gCInventory_PS"));
				if( inventory )
				{
					int stack;
					Game::GiveItem(entity, stack, combatItem.c_str());
					inventory->EquipStackToSlot(stack, (gESlot)1);
				}
			}
			//Disable animation. TEMPORARY SOLUTION!!!!
			gCNPC_PS* npc = dynamic_cast<gCNPC_PS*>(entity->GetPropertySet("gCNPC_PS"));
			if( npc )
			{
				static bCString animation;
				animation = npc->GetCurrentMovementAni();
				animation.Replace("%", "%%");
				const char* name = animation.GetText();
				if( name )
				{
					string ani = name;
					if( ani.find("HoldRight") != -1 )
					{
						Entity(entity).StopPlayAni();
						Entity(entity).StartPlayAni("Hero_Stand_None_1H_P0_Ambient_Loop_N_Fwd_00_%%_01_P0_0.xmot", 0, false, 1.0f, false);
					}
				}
			}
		}
	}
};

void Player::Stream()
{
	if( isSpawned == true )
	{
		if( GetDistance3D(matrix[12], matrix[13], matrix[14], lP.matrix[12], lP.matrix[13], lP.matrix[14]) > 4000.0f || gui2.IsMenuOpen() == true )
			Unspawn();
	}
	else
	{
		if( GetDistance3D(matrix[12], matrix[13], matrix[14], lP.matrix[12], lP.matrix[13], lP.matrix[14]) < 3000.0f && gui2.IsMenuOpen() == false )
			Spawn();
	}
};