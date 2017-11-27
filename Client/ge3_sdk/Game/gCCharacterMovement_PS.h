#ifndef _GCCHARACTERMOVEMENT_PS_H
#define _GCCHARACTERMOVEMENT_PS_H

class DLLIMPORT gCCharacterMovement_PS
	: public eCEntityPropertySet
{
public:
	void SetGoalRotation( const bCQuaternion & );
	void EnableMovementFromSPU( bool );
	void SetTurnSpeedMax(const float &);
	void SetTurnSpeedModifier(const float &);
	void SetTurnAcceleration(const float &);
	void SetTurnDecceleration(const float &);
	void SetSneakModifier(const float &);
	bCVector & GetAlignmentLookAt( void );
	void SetAlignmentLookAt( const bCVector & );
	virtual float GetCurrentSpeedModifier( void ); //this+0x160
	gECharMovementMode GetLastMovementMode( void ) const;
	bool IsSprinting( void ) const;
	bool IsRunning( void ) const;
	bool IsWalking( void ) const;
	bool IsStanding( void ) const;
	bool IsJumping( void ) const;
	bool IsFalling( void ) const;
	bool IsSneaking( void ) const;
	bool IsSwimming( void ) const;
	bool IsDiving( void ) const;
	bool IsBraking( void ) const;
	void StopMovement();
	void SetMovementMode(gECharMovementMode);
};
#endif