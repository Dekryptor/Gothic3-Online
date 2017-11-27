#ifndef _GCSESSION_H
#define _GCSESSION_H
class gCScreenOutputCtrl;
struct bCObjectRefBase;
struct bCEvent;
class DLLIMPORT gCSession
{
public:
	static gCSession const & STDCALL GetSession( void );
	eCEntity * SpawnEntity( const bCString &, bCVector, bool );
	void StartControlNPC( gCEntity * );
	void StopControlNPC( bool );
	bool const IsInTestMode( void ) const;
	void SetTestMode( bool );
	void Stop( void );
	void Pause( void );
	void Resume( void );
	bool SetAttrib( const bCString &, int );
	gCGUIManager* GetGUIManager( void ) const;
	gCScreenOutputCtrl* GetScreenOutputCtrl( void );
	bool IsPaused( void ) const;
	bool IsGameRunning( void ) const;
	bool IsSaveAllowed( void ) const;
	const eCDynamicEntity* GetHero() const;
	int FASTCALL Start(int,int,int,int,int,int,int);
	void TransferDebugEvents(eCEntity &);
	bool GiveAllItems(bool, unsigned long, unsigned long, const bCString &) const;
protected:
	void __stdcall OnResetPlayer(struct bCObjectRefBase*, struct bCEvent*);
};
#endif