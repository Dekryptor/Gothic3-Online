#ifndef _GCFOCUS_PS_H
#define _GCFOCUS_PS_H
class DLLIMPORT gCFocus_PS 
	: public eCEntityPropertySet
{
public:
	eCEntity* FindFocusEntity( bool );
};
#endif