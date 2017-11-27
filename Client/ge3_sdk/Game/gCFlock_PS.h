#ifndef _GCFLOCK_PS_H
#define _GCFLOCK_PS_H
class DLLIMPORT gCFlock_PS :
	public eCEntityPropertySet
{
public:
	const bool* GetAmbientAniPlaying( void );
	void SetAmbientAniPlaying( const bool & );
	void SetIsDead( const bool & );
};
#endif