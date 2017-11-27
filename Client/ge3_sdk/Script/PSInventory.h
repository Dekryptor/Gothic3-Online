#ifndef _PSINVENTORY_H
#define _PSINVENTORY_H
GS_DECLARE_PROPERTYSET( PSInventory, gCInventory_PS )
public:
	//PSInventory(eCEntity*);
	//bool ExecuteItem(int);
	//gESlot GetSlotFromStack(int) const;
	bool EquipStack(int);
	bool UnEquipStack(int);
	bool SetAmount(int, unsigned long);
};
#endif