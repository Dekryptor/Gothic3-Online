#ifndef _GCWORLD_H
#define _GCWORLD_H
class DLLIMPORT gCWorld
{
public:
	bool LoadGameWorld( const bCString &, bool );
	static gCWorld* STDCALL GetCurrentWorld( void );
};
#endif