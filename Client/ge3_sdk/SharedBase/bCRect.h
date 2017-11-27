#ifndef _BCRECT_H
#define _BCRECT_H
class DLLIMPORT bCRect
{
public:
	enum bECoordinate
    {
        bECoordinate_Left,
        bECoordinate_Top,
        bECoordinate_Right,
        bECoordinate_Bottom,
        bECoordinate_Count,
        bECoordinate_ForceDWORD = FORCE_DWORD
    };
    enum bEPoint
    {
        bEPoint_TopLeft,
        bEPoint_BottomRight,
        bEPoint_Count,
        bEPoint_ForceDWORD = FORCE_DWORD
    };

    bool          operator ==             ( bCRect const & ) const;
    bool          operator !=             ( bCRect const & ) const;
    bCPoint &       operator []             ( int );
    bCPoint const & operator []             ( int ) const;
    bCRect          operator -              ( bCPoint const & ) const;
    bCRect          operator +              ( bCPoint const & ) const;
    bCRect          operator &              ( bCRect const & ) const;
    long &         operator ()             ( int );
    long           operator ()             ( int ) const;
    bCRect          operator |              ( bCRect const & ) const;
    bCRect &        operator +=             ( bCPoint const & );
    bCRect &        operator -=             ( bCPoint const & );
    bCRect &        operator &=             ( bCRect const & );
    bCRect &        operator |=             ( bCRect const & );
    bCRect &        operator =              ( bCRect const & );


    bCRect( long, long, long, long );
    bCRect( bCPoint const &, bCPoint const & );
    bCRect( bCRect const & );
    bCRect( void );
   ~bCRect( void );
};
#endif