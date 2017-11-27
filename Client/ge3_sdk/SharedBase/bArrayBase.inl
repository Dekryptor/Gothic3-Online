template< typename T >
void bTArrayBase< T >::Copy( T * _d, T const * _s, int _n )
{
    while( _n-- )
        *_d++ = *_s++;
}

template< typename T >
void bTArrayBase< T >::Delete( T * _e, int _n )
{
    for( ; _n--; _e++ )
        _e->~T();
}

template< typename T >
void bTArrayBase< T >::Move( T * _d, T const * _s, int _n )
{
    if( _n > 0 )
        ::memmove( _d, _s, _n * sizeof( T ) );
}

template< typename T >
void bTArrayBase< T >::New( T * _e, int _n )
{
    g_ZeroMemory( _e, _n * sizeof( T ) );
    for( ; _n--; _e++ )
        ::new( _e ) T;
}

template< typename T >
void bTArrayBase< T >::Init( void )
{
    this->m_pArray = 0;
    this->m_u32Count = 0;
    this->m_u32Capacity = 0;
}

template< typename T >
bTArrayBase< T >::bTArrayBase( void )
{
    this->Init();
}

template< typename T >
bTArrayBase< T >::~bTArrayBase( void )
{
}

template< typename T >
T * bTArrayBase< T >::AccessArray( void )
{
    return this->m_pArray;
}

template< typename T >
T & bTArrayBase< T >::AccessAt( int _i )
{
    return this->m_pArray[ _i ];
}

template< typename T >
typename bTArrayBase< T >::bCConstIterator bTArrayBase< T >::Begin( void ) const
{
    return bCConstIterator( this->GetArray(), 0 );
}

template< typename T >
typename bTArrayBase< T >::bCIterator bTArrayBase< T >::Begin( void )
{
    return bCIterator( this->AccessArray(), 0 );
}

template< typename T >
T const * bTArrayBase< T >::GetArray( void ) const
{
    return this->m_pArray;
}

template< typename T >
T const & bTArrayBase< T >::GetAt( int _i ) const
{
    return this->m_pArray[ _i ];
}

template< typename T >
void bTArrayBase< T >::GetAt( int _i, T & _e ) const
{
    _e = this->GetAt( _i );
}

template< typename T >
int bTArrayBase< T >::GetCapacity( void ) const
{
    return static_cast< int >( this->m_u32Capacity );
}

template< typename T >
int bTArrayBase< T >::GetCount( void ) const
{
    return static_cast< int >( this->m_u32Count );
}

template< typename T >
typename bTArrayBase< T >::bCConstIterator bTArrayBase< T >::End( void ) const
{
    return bCConstIterator( this->GetArray(), this->GetCount() );
}

template< typename T >
typename bTArrayBase< T >::bCIterator bTArrayBase< T >::End( void )
{
    return bCIterator( this->AccessArray(), this->GetCount() );
}

template< typename T >
bool bTArrayBase< T >::IsEmpty( void ) const
{
    return 0 == this->GetCount();
}

template< typename T >
int bTArrayBase< T >::IndexOf( T const & _e ) const
{
    int _i = this->GetCount();
    while( _i-- )
        if ( _e == this->m_pArray[ _i ] )
            return _i;
    return bEIndex_Invalid;
}

template< typename T >
T const & bTArrayBase< T >::operator [] ( int _i ) const
{
    return this->GetAt( _i );
}

template< typename T >
T & bTArrayBase< T >::operator [] ( int _i )
{
    return this->AccessAt( _i );
}