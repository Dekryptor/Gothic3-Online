#ifndef _BCPOINT_H
#define _BCPOINT_H
class DLLIMPORT bCPoint
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
	int m_i32X;
	int m_i32Y;
public:
    void    Clear( void );
    bCPoint GetInvScaled( float ) const;
    bCPoint GetScaled( float ) const;
    long   GetX( void ) const;
    void    GetX( long & ) const;
    long   GetY( void ) const;
    void    GetY( long & ) const;
    void    InvScale( float );
    void    InvTranslate( bCPoint const & );
    void    InvTranslate( long, long );
    void    Scale( float );
   // void    SetPoint( bSPoint const & );
    void    SetPoint( bCPoint const & );
    void    SetPoint( long, long );
    void    SetX( long );
    void    SetY( long );
    void    Translate( bCPoint const & );
    void    Translate( long, long );
public:
                    //operator bSPoint &       ( void );
                    //operator bSPoint *       ( void );
                    //operator bSPoint const & ( void ) const;
                    //operator bSPoint const * ( void ) const;
   // bCPoint const & operator =               ( bSPoint const & );
    bool          operator ==              ( bCPoint const & ) const;
    bool          operator !=              ( bCPoint const & ) const;
    long &         operator []              ( long );
    long           operator []              ( long ) const;
    bCPoint         operator *               ( float ) const;
    bCPoint         operator -               ( bCPoint const & ) const;
    bCPoint         operator -               ( void ) const;
    bCPoint         operator +               ( bCPoint const & ) const;
    bCPoint const & operator +               ( void ) const;
    bCPoint         operator /               ( float ) const;
    bCPoint &       operator *=              ( float );
    bCPoint const & operator +=              ( bCPoint const & );
    bCPoint const & operator -=              ( bCPoint const & );
    bCPoint &       operator /=              ( float );
    bCIStream &     operator <<              ( bCIStream & );
    bCOStream &     operator >>              ( bCOStream & ) const;
    bCPoint const & operator =               ( bCPoint const & );
public:
    //bCPoint( bSPoint const & );
    bCPoint( long, long );
    bCPoint( bCPoint const & );
    bCPoint( void );
   ~bCPoint( void );
};
#endif