#ifndef _BTOBJARRAY_H
#define _BTOBJARRAY_H

template< typename T >
class bTObjArray :
    public bTArrayBase< T >
{
public:
    void Add( T const & _e );
    T &  AddNew( void );
    void Clear( void );
    void CopyFrom( bTObjArray< T > const & _s );
    void CopyTo( bTObjArray< T > & _d ) const;
    void InsertAt( int _i, T const & _e );
    T &  InsertNewAt( int _i );
    void Remove( T const & _e );
    void RemoveAll( void );
    void RemoveAt( int _i );
    void Reserve( int _n );
    void SetAt( int _i, T const & _e );
    void SetCount( int _n );
public:
    bTObjArray< T > & operator = ( bTObjArray< T > const & _s );
public:
             bTObjArray( bTObjArray< T > const & _s );
    explicit bTObjArray( int _n );
             bTObjArray( void );
            ~bTObjArray( void );
};

#include "bTObjectArray.inl"

#endif