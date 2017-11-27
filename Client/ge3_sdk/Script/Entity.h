#ifndef _ENTITY_H
#define _ENTITY_H
#pragma warning( push )
#pragma warning( disable : 4251 )
class gCEntity;
enum gEAction;
enum gEPhase;
class DLLIMPORT Entity
{
public:
	Entity( void );
	Entity( const Entity & );
	Entity( const eCEntity * );
	//Entity( const eCEntityProxy & );
	Entity( const bCPropertyID & );
public:
	template< typename PS >
    inline PS & AccessPropertySet( void );
    template< typename PS >

    inline PS const & GetPropertySet( void ) const;
    template< typename PSP >
    inline PSP & AccessPropertySetProperty( void );
    template< typename PSP >
    inline PSP const & GetPropertySetProperty( void ) const;
    template< typename PS >
    inline typename PS::EnginePropertySet * AccessEnginePropertySet( void );
    template< typename PS >
    inline typename PS::EnginePropertySet const * GetEnginePropertySet( void ) const;

	gCEntity * GetGameEntity( void ) const;
	static Entity STDCALL GetPlayer( void );
	static Entity STDCALL GetWorldEntity( void );
	static Entity STDCALL GetCameraEntity( void );
	//static PSCamera STDCALL GetCamera( void );
	bool IsItem( void ) const;
	bool IsCharacter( void ) const;
	bool IsNPC( void ) const;
	bool IsPlayer( void ) const;
	bool IsInteractObject( void ) const;
	bool Teleport( const Entity & );
	bCVector GetPosition( void ) const;
	bCString GetName( void ) const; //Player instance
	bCString GetDisplayName( void ) const; //Player instance
	bCUnicodeString GetFocusName( void ) const; //Player name ex. "Ja"
	
	static void STDCALL SetWorldTime( float );
	static float STDCALL GetWorldTime( void );
	static void STDCALL SetPlayingTime( float );
	static float STDCALL GetPlayingTime( void );
	static Entity STDCALL GetEntity( bCString );
	static Entity STDCALL Spawn( Template, const bCMatrix & );
	bool IsDead( void ) const;
	bool IsDown( void ) const;
	bool IsReady( void ) const;
	bool IsStanding( void ) const;
	bool IsFalling( void ) const;
	bool IsSwimming( void ) const;
	bool IsDiving( void ) const;
	bool IsSprinting( void ) const;
	bool IsJumping( void ) const;

	//For creating entity use gCSession::SpawnEntity
	void StartPlayAni( bCString name, int playCount, bool opposite, float speed, bool );
	void StopPlayAni( void );
	void MoveTo(const bCMatrix &);
	bCString GetSkeletonName( void ) const;
	gEPhase GetCurrentAniPhase( void ) const;
	bCString GetAni( gEAction, gEPhase ) const;
	void SetAlignmentTarget(const Entity &);
	void Kill( void );
	void StartOutput( bCString );
	void MoveTo(const Entity &);
	bCVector GetAtVector( void ) const;
	bCMatrix GetPose( void ) const;
	void StartTransform(Entity&, float, bool);
	void EndTransform( void );
	static bTObjArray< Entity > STDCALL GetEntities( void );
	static bTObjArray< Entity > STDCALL GetNPCs( void );
	void EnableRendering( bool );

	Entity & operator =          ( Entity const & );
    bool   operator ==         ( Entity const & ) const;
    bool   operator !=         ( Entity const & ) const;
           operator eCEntity * ( void ) const;

};
#include "Entity.inl"
#pragma warning( pop )
#endif