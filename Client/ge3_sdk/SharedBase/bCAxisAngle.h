#ifndef _BCAXISANGLE_H
#define _BCAXISANGLE_H

class DLLIMPORT bCAxisAngle
{
private:
    bCVector m_vecAxis;
    float  m_fAngle;
public:
    float &        AccessAngle( void );
    bCVector &       AccessAxis( void );
    void             Clear( void );
    float          GetAngle( void ) const;
    void             GetAngle( float & ) const;
    bCVector const & GetAxis( void ) const;
    void             GetAxis( bCVector & ) const;
    //bCEulerAngles    GetEulerAngles( void ) const;
    bCQuaternion     GetQuaternion( void ) const;
    bool           IsEqual( bCAxisAngle const & ) const;
    void             SetAngle( float );
    void             SetAxis( bCVector const & );
    void             SetAxisAngle( bCAxisAngle const & );
   // void             SetAxisAngle( bCEulerAngles const & );
    void             SetAxisAngle( bCQuaternion const & );
    void             SetAxisAngle( bCVector const &, float );
public:
   // explicit bCAxisAngle( bCEulerAngles const & );
    explicit bCAxisAngle( bCQuaternion const & );
             bCAxisAngle( bCVector const &, float );
             bCAxisAngle( bCAxisAngle const & );
             bCAxisAngle( void );
            ~bCAxisAngle( void );
};

#endif