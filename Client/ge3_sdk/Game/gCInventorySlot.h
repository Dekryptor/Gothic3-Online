#ifndef _GCINVENTORYSLOT_H
#define _GCINVENTORYSLOT_H
enum gEEquipSlot
{
    gEEquipSlot_None         = 0x00000000,
    gEEquipSlot_MeleeWeapon  = 0x00000001,
    gEEquipSlot_MeleeShield  = 0x00000002,
    gEEquipSlot_RangedWeapon = 0x00000003,
    gEEquipSlot_RangedAmmo   = 0x00000004,
    gEEquipSlot_Amulet       = 0x00000005,
    gEEquipSlot_Ring1        = 0x00000006,
    gEEquipSlot_Ring2        = 0x00000007,
    gEEquipSlot_Armor        = 0x00000008,
    gEEquipSlot_Helmet       = 0x00000009,
    gEEquipSlot_ForceDWORD   = FORCE_DWORD
};
enum gESlot
{
	gESlot_ForceDWORD = FORCE_DWORD
};
class DLLIMPORT gCInventorySlot
{
public:
	static gESlot STDCALL GetSlot( gEEquipSlot ); //Probably for local player
};
#endif