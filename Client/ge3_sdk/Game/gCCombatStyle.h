#ifndef _GCCOMBATSTYLE_H
#define _GCCOMBATSTYLE_H
enum gECombatMode
{
    gECombatMode_None       = 0x00000000,
    gECombatMode_Carry      = 0x00000001,
    gECombatMode_Melee      = 0x00000002,
    gECombatMode_Ranged     = 0x00000003,
    gECombatMode_Magic      = 0x00000004,
    gECombatMode_Cast       = 0x00000005,
    gECombatMode_ForceDWORD = FORCE_DWORD
};
#endif