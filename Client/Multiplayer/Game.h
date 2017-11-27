#ifndef _MPGAME_H
#define _MPGAME_H

namespace Game
{
	int GetTicks();
	void DoubleClick(int x, int y);
	void SetWindowName(const char* text);
	void ForceDisableTestmode();
	void GetCompleteMatrix(bCMatrix mat, float (&completeMat)[17]);
	bCMatrix GetDefaultMatrix(float (&completeMat)[17]);
	eCEntity* GiveItem(eCEntity* player, int& stackResult, bCString itemName, unsigned long amount = 1);
	void RespawnHero();
	void RepairNicknames();
	void CompleteHeal(eCEntity* entity);
	const bCString GetRoutineTask( gCScriptRoutine_PS* pThis );
};
#endif