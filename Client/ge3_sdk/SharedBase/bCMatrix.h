#ifndef _BCMATRIX_H
#define _BCMATRIX_H
class DLLIMPORT bCMatrix
{
public:
    enum bEElement
    {
        bEElement_11,
        bEElement_12,
        bEElement_13,
        bEElement_14,
        bEElement_21,
        bEElement_22,
        bEElement_23,
        bEElement_24,
        bEElement_31,
        bEElement_32,
        bEElement_33,
        bEElement_34,
        bEElement_41,
        bEElement_42,
        bEElement_43,
        bEElement_44,
        bEElement_Count,
        bEElement_ForceDWORD = FORCE_DWORD
    };
    enum bERow
    {
        bERow_XAxis,
        bERow_YAxis,
        bERow_ZAxis,
        bERow_Translation,
        bERow_Count,
        bERow_ForceDWORD = FORCE_DWORD
    };
    enum bEColumn
    {
        bEColumn_X,
        bEColumn_Y,
        bEColumn_Z,
        bEColumn_Reserved,
        bEColumn_Count,
        bEColumn_ForceDWORD = FORCE_DWORD
    };
private:
    union
    {
        float m_fElements[ bEElement_Count ];                 // 0000
        float m_fRowColumn[ bERow_Count ][ bEColumn_Count ];  // 0000
    };
    // sizeof(bCMatrix)                                            0040
protected:
   /* bCVector4 &       AccessRow4( int );
    bCVector &        AccessRow( int );*/
    bCMatrix          GetInvertedExcentric( void ) const;
    void              GetInvertedExcentric( bCMatrix & ) const;
   /* bCVector4 const & GetRow4( int ) const;
    bCVector const &  GetRow( int ) const;
    void              GetRow( int, bCVector4 & ) const;
    void              GetRow( int, bCVector & ) const;*/
    void              InvertExcentric( void );
    void              ValidateReserved( void );
public:
    static bCMatrix const & STDCALL GetIdentity( void );
    static void             STDCALL GetIdentity( bCMatrix & );
    static bCMatrix const & STDCALL GetZero( void );
public:
    float &         AccessElement( int );
    float &         AccessElement( int, int );
    bCVector &        AccessTranslation( void );
   // bCVector4 &       AccessTranslation4( void );
    bCVector &        AccessXAxis( void );
  //  bCVector4 &       AccessXAxis4( void );
    bCVector &        AccessYAxis( void );
    //bCVector4 &       AccessYAxis4( void );
    bCVector &        AccessZAxis( void );
    //bCVector4 &       AccessZAxis4( void );
    void              Add( bCMatrix const & );
    void              Clear( void );
    void              ClearRotation( void );
    void              Divide( float );
    bCVector          GetColumn( int ) const;
   // bCVector4         GetColumn4( int ) const;
    void              GetColumn( int, bCVector & ) const;
    //void              GetColumn( int, bCVector4 & ) const;
    void              GetColumn( int, float [ bERow_Count ] ) const;
    float           GetDeterminant( void ) const;
    float           GetDeterminantAdjoint( int, int ) const;
    float           GetDeterminantRotation( void ) const;
    bCMatrix          GetDifference( bCMatrix const & ) const;
    void              GetDifference( bCMatrix &,  bCMatrix const & ) const;
    float           GetElement( int ) const;
    float           GetElement( int, int ) const;
    void              GetElement( int, float & ) const;
    void              GetElement( int, int, float & ) const;
    bCMatrix          GetInverted( void ) const;
    void              GetInverted( bCMatrix & ) const;
    bCMatrix          GetNegated( void ) const;
    void              GetNegated( bCMatrix & ) const;
    bCMatrix          GetOrthogonalized( void ) const;
    void              GetOrthogonalized( bCMatrix & ) const;
    bCMatrix          GetOrthonormalized( void ) const;
    void              GetOrthonormalized( bCMatrix & ) const;
    bCMatrix          GetProduct( bCMatrix const & ) const;
    bCMatrix          GetProduct( float ) const;
    void              GetProduct( bCMatrix &,  bCMatrix const & ) const;
    void              GetProduct( bCMatrix &,  float ) const;
    bCMatrix          GetProductPrefix( bCMatrix const & ) const;
    void              GetProductPrefix( bCMatrix &,  bCMatrix const & ) const;
    bCMatrix          GetPureRotation( void ) const;
    bCVector          GetPureScaling( void ) const;
    bCMatrix          GetQuotient( float ) const;
    void              GetQuotient( bCMatrix &,  float ) const;
   // bCMatrix          GetRotated( bCAxisAngle const & ) const;
    //bCMatrix          GetRotated( bCEulerAngles const & ) const;
    //CMatrix          GetRotated( bCQuaternion const & ) const;
    /*void              GetRotated( bCMatrix &,  bCAxisAngle const & ) const;
    void              GetRotated( bCMatrix &,  bCEulerAngles const & ) const;
    void              GetRotated( bCMatrix &,  bCQuaternion const & ) const;*/
    bCMatrix          GetRotatedByAxisX( float ) const;
    void              GetRotatedByAxisX( bCMatrix &,  float ) const;
    bCMatrix          GetRotatedByAxisY( float ) const;
    void              GetRotatedByAxisY( bCMatrix &,  float ) const;
    bCMatrix          GetRotatedByAxisZ( float ) const;
    void              GetRotatedByAxisZ( bCMatrix &,  float ) const;
    bCMatrix          GetRotatedByLocalAxisX( float ) const;
    void              GetRotatedByLocalAxisX( bCMatrix &,  float ) const;
    bCMatrix          GetRotatedByLocalAxisY( float ) const;
    void              GetRotatedByLocalAxisY( bCMatrix &,  float ) const;
    bCMatrix          GetRotatedByLocalAxisZ( float ) const;
    void              GetRotatedByLocalAxisZ( bCMatrix &,  float ) const;
  /*  bCMatrix          GetRotatedLocal( bCAxisAngle const & ) const;
    bCMatrix          GetRotatedLocal( bCEulerAngles const & ) const;
    bCMatrix          GetRotatedLocal( bCQuaternion const & ) const;
    void              GetRotatedLocal( bCMatrix &,  bCAxisAngle const & ) const;
    void              GetRotatedLocal( bCMatrix &,  bCEulerAngles const & ) const;
    void              GetRotatedLocal( bCMatrix &,  bCQuaternion const & ) const;*/
    void              GetRotation( bCMatrix & ) const;
  //  void              GetRotation( bCMatrix3 & ) const;
    bCMatrix          GetRotation( void ) const;
  //  bCMatrix3         GetRotation3( void ) const;
    void              GetRow( int, float [ bEColumn_Count ] ) const;
    bCMatrix          GetSum( bCMatrix const & ) const;
    void              GetSum( bCMatrix &,  bCMatrix const & ) const;
    void              GetTranslation( bCVector & ) const;
    //void              GetTranslation( bCVector4 & ) const;
    bCVector const &  GetTranslation( void ) const;
    //bCVector4 const & GetTranslation4( void ) const;
    void              GetXAxis( bCVector & ) const;
    //void              GetXAxis( bCVector4 & ) const;
    bCVector const &  GetXAxis( void ) const;
    //bCVector4 const & GetXAxis4( void ) const;
    void              GetYAxis( bCVector & ) const;
    //void              GetYAxis( bCVector4 & ) const;
    bCVector const &  GetYAxis( void ) const;
    //bCVector4 const & GetYAxis4( void ) const;
    void              GetZAxis( bCVector & ) const;
    //void              GetZAxis( bCVector4 & ) const;
    bCVector const &  GetZAxis( void ) const;
    //bCVector4 const & GetZAxis4( void ) const;
    void              Invert( void );
    bool            IsEqual( bCMatrix const & ) const;
    bool            IsExcentric( void ) const;
    bool            IsIdentity( void ) const;
    bool const      IsOrthogonal( void ) const;
    bool const      IsOrthonormal( void ) const;
    bool const      IsValid( void ) const;
    void              LookAt( bCVector const &,  bCVector const & );
    void              LookAt( bCVector const & );
    /*void              ModifyRotation( bCAxisAngle const & );
    void              ModifyRotation( bCEulerAngles const & );
    void              ModifyRotation( bCMatrix3 const & );
    void              ModifyRotation( bCQuaternion const & );*/
    void              ModifyRotationAxisX( float );
    void              ModifyRotationAxisY( float );
    void              ModifyRotationAxisZ( float );
    void              ModifyScaling( bCVector const & );
    void              ModifyScaling( float );
    void              ModifyTranslation( bCVector const & );
    void              ModifyXAxis( bCVector const & );
  //  void              ModifyXAxis( bCVector4 const & );
    void              ModifyYAxis( bCVector const & );
    //void              ModifyYAxis( bCVector4 const & );
    void              ModifyZAxis( bCVector const & );
    //void              ModifyZAxis( bCVector4 const & );
    void              Multiply( bCMatrix const & );
    void              Multiply( float );
    void              Negate( void );
    void              Orthogonalize( void );
    void              Orthonormalize( void );
    void              PrintDebug( bCString & );
    void              ReverseMultiply( bCMatrix const & );
    /*void              Rotate( bCAxisAngle const & );
    void              Rotate( bCEulerAngles const & );
    void              Rotate( bCQuaternion const & );*/
    void              RotateAxisX( float );
    void              RotateAxisY( float );
    void              RotateAxisZ( float );
   /* void              RotateLocal( bCAxisAngle const & );
    void              RotateLocal( bCEulerAngles const & );
    void              RotateLocal( bCQuaternion const & );*/
    void              RotateLocalAxisX( float );
    void              RotateLocalAxisY( float );
    void              RotateLocalAxisZ( float );
    void              Scale( bCVector const & );
    void              Scale( float );
    void              SetElement( int, int, float );
    void              SetElement( int, float );
    void              SetIdentity( void );
    void              SetIdentityRotation( void );
    void              SetMatrix( bCMatrix const & );
   /* void              SetMatrix( bCAxisAngle const &, bCVector const & );
    void              SetMatrix( bCEulerAngles const &, bCVector const & );
    void              SetMatrix( bCMotion const & );
    void              SetMatrix( bCQuaternion const &, bCVector const & );
    void              SetMatrix( bCVector const &, bCEulerAngles const &, bCVector const & );
    void              SetMatrix( bCVector const &, bCQuaternion const &, bCVector const & );*/
    void              SetMatrix( float );
    void              SetMatrix( float const [ bERow_Count ][ bEColumn_Count ] );
    void              SetMatrix( float const [ bEElement_Count ] );
   // void              SetMatrix( bCVector4 const [ bERow_Count ] );
    void              SetMatrix( bCVector const [ bERow_Count ] );
    //void              SetRow( int, bCVector4 const & );
    void              SetRow( int, bCVector const & );
    void              SetRow( int, float const [ bEColumn_Count ] );
    void              SetToCrossProduct( bCVector const & );
    /*void              SetToProduct( bCMatrix const &,  bCMatrix const & );  // inline local: static bCMatrix matProduct;
    void              SetToRotation( bCAxisAngle const & );
    void              SetToRotation( bCEulerAngles const & );
    void              SetToRotation( bCQuaternion const & );*/
    void              SetToRotationAxisX( float );
    void              SetToRotationAxisY( float );
    void              SetToRotationAxisZ( float );
    void              SetToScaling( bCVector const & );
    void              SetToScaling( float );
    void              SetToTranslation( bCVector const & );
   // void              SetXAxis( bCVector4 const & );
    void              SetXAxis( bCVector const & );
   // void              SetYAxis( bCVector4 const & );
    void              SetYAxis( bCVector const & );
    //void              SetZAxis( bCVector4 const & );
    void              SetZAxis( bCVector const & );
    void              Sub( bCMatrix const & );
    void              Transpose( void );
    void              TransposeRotation( void );
	void				Rotate( const bCAxisAngle & );

public:
    bool           operator == ( bCMatrix const & ) const;
    bool           operator != ( bCMatrix const & ) const;
    float &        operator [] ( int );
    float          operator [] ( int ) const;
    bCMatrix         operator *  ( bCMatrix const & ) const;
    //bCMatrix         operator *  ( bCAxisAngle const & ) const;
    //bCMatrix         operator *  ( bCEulerAngles const & ) const;
    //bCMatrix         operator *  ( bCQuaternion const & ) const;
    bCMatrix         operator *  ( float ) const;
    bCVector         operator *  ( bCVector const & ) const;
    bCMatrix         operator -  ( bCMatrix const & ) const;
    bCMatrix         operator -  ( void ) const;
    bCMatrix         operator +  ( bCMatrix const & ) const;
    bCMatrix         operator /  ( float ) const;
    float &        operator () ( int, int );
    bCVector &       operator () ( int );
    bCVector const & operator () ( int ) const;
    float          operator () ( int, int ) const;
    bCMatrix         operator ~  ( void ) const;
    bCMatrix &       operator *= ( bCMatrix const & );
    /*bCMatrix &       operator *= ( bCAxisAngle const & );
    bCMatrix &       operator *= ( bCEulerAngles const & );
    bCMatrix &       operator *= ( bCQuaternion const & );*/
    bCMatrix &       operator *= ( float );
    bCMatrix &       operator += ( bCMatrix const & );
    bCMatrix &       operator -= ( bCMatrix const & );
    bCMatrix &       operator /= ( float );
    bCIStream &      operator << ( bCIStream & );
    bCOStream &      operator >> ( bCOStream & ) const;
    bCMatrix &       operator =  ( bCMatrix const & );
public:
             bCMatrix( bCAxisAngle const &,  bCVector const & );
       //      bCMatrix( bCEulerAngles const &,  bCVector const & );
             bCMatrix( bCQuaternion const &,  bCVector const & );
    explicit bCMatrix( float );
    explicit bCMatrix( float const [ bEElement_Count ] );
    explicit bCMatrix( float [ bERow_Count ][ bEColumn_Count ] );
    explicit bCMatrix( bCVector const [ bERow_Count ] );
    //explicit bCMatrix( bCVector4 const [ bERow_Count ] );
             bCMatrix( bCMatrix const & );
            bCMatrix( void );
            ~bCMatrix( void );
};

typedef bCMatrix bCMatrix4;
#endif