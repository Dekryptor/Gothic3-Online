#ifndef _GCCHARACTERCONTROL_PS
#define _GCCHARACTERCONTROL_PS
enum gECharMovementMode
{
	gECharMovementMode_Stand = 1,
	gECharMovementMode_Sneak = 2, //Bugged at this moment
	gECharMovementMode_Walk = 3,
	gECharMovementMode_Run = 4,
	gECharMovementMode_Sprint = 5,
    gECharMovementMode_ForceDWORD = FORCE_DWORD
};

class DLLIMPORT gCCharacterControl_PS
{
public:
	void SetWishedMovementMode(gECharMovementMode);
	//GetWishedMovementMode = (*(int*)((DWORD)charControl+0x0AC))
};

#endif