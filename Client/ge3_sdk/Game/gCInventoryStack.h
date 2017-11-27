#ifndef _GCINVENTORYSTACK_H
#define _GCINVENTORYSTACK_H
class DLLIMPORT gCInventoryStack
	: public gCInventorySlot
{
public:
	bool IsEquipped( const eCEntity* ) const;
	void SetAmount( const int & );
};
#endif