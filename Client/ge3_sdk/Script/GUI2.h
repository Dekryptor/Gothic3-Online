#ifndef _GUI2_H
#define _GUI2_H
//Taken from Risen SDK, some functions must be changed for G3
enum gEHudPage
{
	hUnk1,
	hUnk2,
	hUnk3
};

enum gEGameLogType
{
	lUnk1,
	lUnk2,
	lUnk3
};

enum gEHudMode
{
	mUnk1,
	mUnk2,
	mUnk3
};

class DLLIMPORT GUI2
{
protected:
	bool m_bLogMessagesEnabled;
public:
    bool     AcceptResolution( void );
    bool     ApplyResolution( void );
    bool     CanContinue( void );
    void       ClearGameLog( void );
    bool     Close( gEHudPage );
    void       Continue( void );
    bool     DoModal( bCString, int &, void* );
    bool     GetEnableLogMessages( void ) const;
    //gEHudMode  GetMode( void ) const;
    int      GetNumRefreshRates( int );
    int      GetNumResolutions( void );
    //gEPageMode GetPageMode( void ) const;
    int      GetPendingRefreshRate( void );
    int      GetPendingResolution( void );
    unsigned int    GetRefreshRate( int, int );
    bCPoint    GetResolution( int );
    int      GetSliderThreshold( void ) const;
    void       Init( void );
    bool     IsBrowsing( void ) const;
    bool     IsBrowsingCraftSelect( void );
    bool     IsBrowsingGame( void ) const;
    bool     IsBrowsingItemSelect( void );
    bool     IsBrowsingLoot( void );
    bool     IsBrowsingMap( void ) const;
    bool     IsBrowsingMenu( void ) const;
    bool     IsBrowsingPickpocket( void );
    bool     IsConsoleVisible( void ) const;
    bool     IsEditing( void ) const;
    bool     IsLoading( void ) const;
    bool     IsVisible( gEHudPage ) const;
	bool	 IsMenuOpen( void );
    int      ModalAcceptResolution( void );
	void 	 StartSay(const Entity &, const bCUnicodeString &, bool);
	void	 StopSay(void);
    int      ModalClosePage( gEHudPage );
    int      ModalDelete( bCUnicodeString );
    int      ModalLoad( bCUnicodeString );
    int      ModalNewGame( void );
    int      ModalOverride( bCUnicodeString );
    int      ModalQuitGame( void );
    int      ModalResetKeyboard( void );
    int      ModalSave( bCUnicodeString );
    int      ModalStackAccept( int, bCUnicodeString );
    int      ModalStackAmount( int, int, int &, bCUnicodeString );
    bool     Open( gEHudPage );
    bool     OpenAlchemy( void );
    bool     OpenAltar( void );
    bool     OpenAnvil( void );
    bool     OpenCooking( void );
    bool     OpenCoolWeapon( void );
    bool     OpenForge( void );
    bool     OpenFrying( void );
    bool     OpenGoldsmith( void );
    bool     OpenGrindStone( void );
    bool     OpenLoot( void );
    bool     OpenPickpocket( unsigned int );
    bool     OpenWriteScroll( void );
    void       PlayVideo( bCString const &, bool );
    void       Log( bCUnicodeString const &, gEGameLogType);
    void       LogF( gEGameLogType, char const*, ... );
    void       PrintItemLog( Entity, int );
    bool     RestoreResolution( void );
    void       RestoreUserPageMode( void ) const;
   // bool     SendAbort( gEHudPage );
    bool     SendGameMessage( int, int, int, gEHudPage, bool );
    bool     SendGetSaveGameSelect( bCUnicodeString &, gEHudPage );
	void	 PrintGameMessage( const bCUnicodeString &, gEGameMessageType);
   // bool     SendLockpickInfo( Entity, int, gELockCombi );
    bool     SendLoot( Entity, int, gEHudPage );
    bool     SendSaveGameChanged( gEHudPage );
    bool     SendSetSaveGameSelect( bCUnicodeString const &, gEHudPage );
    void       SetCrossHairSize( float );
    void       SetEnableLogMessages( bool );
    //void       SetPageMode( gEPageMode const &, bool );
    void       SetPendingRefreshRate( int );
    void       SetPendingResolution( int );
    bool     Show( gEHudPage, bool );
    void       ShowCrossHair( bool );
    void       ShowPicture( bCString const & );
    bool     ShowPropertyEditor( Entity, bool );
    void       ShowSubtitle( bCUnicodeString const & );
    void       ToggleEntityDebug( void );
private:
    GUI2( void );  // hide constructor
   ~GUI2( void );  // hide destructor
private:
    GUI2 & operator = ( GUI2 const & );  // hide copy assignment operator
};

DLLIMPORT_EXTC GUI2 gui2;
#endif