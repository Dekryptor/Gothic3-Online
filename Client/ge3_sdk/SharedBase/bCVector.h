#ifndef _BCVECTOR_H
#define _BCVECTOR_H
#pragma warning( push )
#pragma warning( disable : 4201 )
class bCMatrix;
class bCMatrix3;
class DLLIMPORT bCVector
{
public:
	enum bECoordinate
	{
		bECoordinate_X,
		bECoordinate_Y,
		bECoordinate_Z,
		bECoordinate_Count,
		bECoordinate_ForceDWORD = FORCE_DWORD
	};
private:
	union
	{
		float m_fCoordinates[ bECoordinate_Count ];
		struct
		{
			float m_fX;
			float m_fY;
			float m_fZ;
		};
	};
public:
	bCVector( void );
	bCVector( float, float, float );
	bCVector( float );
	void GetCoordinates( float &, float &, float & );
	void SetX( const float & );
	void SetZ( const float & );
	void SetVector( float );
	void Clear( void );
	void SetCoordinates( float, float, float );
	void InvTranslate( const bCVector & );
	void Translate( const bCVector & );
	const bCVector & NormalizeApprox( void );
	float GetAngleDeg( bCVector & ) const;
	bCVector GetLerp(const bCVector&, float) const;
	bCVector GetSlerp(const bCVector &, float) const;
	bCVector GetNormalizedSafe( void ) const;
	bCVector GetNormalized( void ) const;

	bool          operator ==             ( bCVector const & ) const;
    bool          operator !=             ( bCVector const & ) const;
    float &       operator []             ( int );
    float const & operator []             ( int ) const;
    bCVector        operator *              ( bCVector const & ) const;
    bCVector        operator *              ( bCMatrix const & ) const;
    bCVector        operator *              ( float ) const;
    bCVector        operator -              ( bCVector const & ) const;
    bCVector        operator -              ( void ) const;
    bCVector        operator +              ( bCVector const & ) const;
    bCVector        operator /              ( bCMatrix const & ) const;
    bCVector        operator /              ( float ) const;
    bCVector &      operator *=             ( bCVector const & );
    bCVector &      operator *=             ( bCMatrix3 const & );
    bCVector &      operator *=             ( bCMatrix const & );
    bCVector &      operator *=             ( float );
    bCVector &      operator +=             ( bCVector const & );
    bCVector &      operator -=             ( bCVector const & );
    bCVector &      operator /=             ( bCMatrix3 const & );
    bCVector &      operator /=             ( bCMatrix const & );
    bCVector &      operator /=             ( float );
    bCVector &      operator =              ( bCVector const & );
};
#pragma warning( pop )
typedef bCVector bCVector3;
#endif