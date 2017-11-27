#ifndef _GCENTITY_H
#define _GCENTITY_H
class gCItem_PS;
class DLLIMPORT gCEntity : public eCEntity
{
protected:
	gCEntity( void );
	gCEntity( const gCEntity & );
	virtual ~gCEntity( void );
public:
	virtual gCEntity* DoClone( void ) const;
	virtual void Destroy( void );
	virtual bool CreateFromTemplate( const bCString & );
	eCEntity* GetWeapon( bool ) const;
	gCItem_PS * GetWeaponItem( bool ) const;
	static gECombatMode STDCALL GetCombatMode( eCEntity* );
	bool STDCALL IsDead(eCEntity *);
	
};
#endif