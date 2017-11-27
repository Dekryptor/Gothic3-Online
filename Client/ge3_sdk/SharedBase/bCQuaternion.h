#ifndef _BCQUATERNION_H
#define _BCQUATERNION_H
class bCMatrix;
class bCAxisAngle;
class DLLIMPORT bCQuaternion
{
public:
	bCQuaternion(float, float, float, float);
	bCQuaternion GetProduct(float) const;
	bCVector GetTransformedVector( const bCVector & ) const;
	float GetMagnitude( void ) const;
	float GetY( void ) const;
	bCMatrix GetMatrix( void ) const;
	float GetW( void ) const;
	float GetZ( void ) const;
	float GetX( void ) const;
	void RotateAxisX( float );
	void RotateAxisZ( float );
	void GetRotatedAxisX( bCQuaternion&, float ) const;
	void GetRotatedAxisZ( bCQuaternion&, float ) const;
	bCAxisAngle         GetAxisAngle( void ) const;

	explicit bCQuaternion( bCAxisAngle const & );
	explicit bCQuaternion( bCMatrix const & );
	bCQuaternion( void );
	~bCQuaternion( void );
};
#endif