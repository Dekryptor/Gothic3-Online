#ifndef _GCITEM_PS
#define _GCITEM_PS
class DLLIMPORT gCItem_PS
	: public eCEntityPropertySet
{
public:
	void SetAmount( const unsigned long & );
	bool IsEquipped( void );
	void SetSlot( gESlot );
};
#endif