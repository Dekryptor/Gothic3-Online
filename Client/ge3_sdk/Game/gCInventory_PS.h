#ifndef _GCINVENTORY_PS_H
#define _GCINVENTORY_PS_H
class gCArmorSet_PS;
class DLLIMPORT gCInventory_PS
	: public eCEntityPropertySet
{
public:
	int InsertStack(eCEntity*);
	bool EquipStack(int);
	bool UnEquipStack(int);
	bool DeleteItems(int, unsigned int);
	bool DeleteStack(int);
	bool IsEquipped(const gCArmorSet_PS *);
	bool IsValidIndex(int) const;
	bool ClearDefaultItems(void);
	eCEntity* DropSlot(gESlot, const bCMatrix *);
	eCEntity* DropStack(int, const bCMatrix *);
	const gCInventoryStack* GetStack(int) const;
	bool EquipStackToSlot(int, gESlot);

};
#endif