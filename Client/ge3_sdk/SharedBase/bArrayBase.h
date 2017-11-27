#ifndef _B_ARRAYBASE_H
#define _B_ARRAYBASE_H

#define GE_DECLARE_ARRAY_ITERATORS()                                                   \
public:                                                                                \
    class bCIterator;                                                                  \
    class bCConstIterator                                                              \
    {                                                                                  \
    protected:                                                                         \
        int m_iIndex;                                                                \
        T *   m_pArray;                                                                \
    public:                                                                            \
        T const & operator * ( void ) const                                            \
        {                                                                              \
            return this->m_pArray[ this->m_iIndex ];                                   \
        }                                                                              \
        T const & operator [] ( int _n ) const                                       \
        {                                                                              \
            return this->m_pArray[ this->m_iIndex + _n ];                              \
        }                                                                              \
        bCConstIterator operator ++ ( int )                                          \
        {                                                                              \
            bCConstIterator _x = *this;                                                \
            ++*this;                                                                   \
            return _x;                                                                 \
        }                                                                              \
        bCConstIterator & operator ++ ( void )                                         \
        {                                                                              \
            this->m_iIndex++;                                                          \
            return *this;                                                              \
        }                                                                              \
        bCConstIterator operator -- ( int )                                          \
        {                                                                              \
            bCConstIterator _x = *this;                                                \
            --*this;                                                                   \
            return _x;                                                                 \
        }                                                                              \
        bCConstIterator & operator -- ( void )                                         \
        {                                                                              \
            this->m_iIndex--;                                                          \
            return *this;                                                              \
        }                                                                              \
        bCConstIterator & operator += ( int _n )                                     \
        {                                                                              \
            this->m_iIndex += _n;                                                      \
            return *this;                                                              \
        }                                                                              \
        bCConstIterator & operator -= ( int _n )                                     \
        {                                                                              \
            this->m_iIndex -= _n;                                                      \
            return *this;                                                              \
        }                                                                              \
        bCConstIterator operator + ( int _n ) const                                  \
        {                                                                              \
            bCConstIterator _x = *this;                                                \
            return _x += _n;                                                           \
        }                                                                              \
        bCConstIterator operator - ( int _n ) const                                  \
        {                                                                              \
            bCConstIterator _x = *this;                                                \
            return _x -= _n;                                                           \
        }                                                                              \
        bCConstIterator operator - ( bCConstIterator const & _x ) const                \
        {                                                                              \
            return (this->m_pArray + this->m_iIndex) - (_x.m_pArray + _x.m_iIndex);    \
        }                                                                              \
        bool operator == ( bCConstIterator const & _x ) const                        \
        {                                                                              \
            return (this->m_iIndex == _x.m_iIndex) && (this->m_pArray == _x.m_pArray); \
        }                                                                              \
        bool operator != ( bCConstIterator const & _x ) const                        \
        {                                                                              \
            return !(*this == _x);                                                     \
        }                                                                              \
        bool operator < ( bCConstIterator const & _x ) const                         \
        {                                                                              \
            return (this->m_pArray + this->m_iIndex) < (_x.m_pArray + _x.m_iIndex);    \
        }                                                                              \
        bool operator > ( bCConstIterator const & _x ) const                         \
        {                                                                              \
            return _x < *this;                                                         \
        }                                                                              \
        bool operator <= ( bCConstIterator const & _x ) const                        \
        {                                                                              \
            return !(_x < *this);                                                      \
        }                                                                              \
        bool operator >= ( bCConstIterator const & _x ) const                        \
        {                                                                              \
            return !(*this < _x);                                                      \
        }                                                                              \
        bCConstIterator( bCIterator const & _x ) :                                     \
            m_iIndex( _x.m_iIndex ),                                                   \
            m_pArray( _x.m_pArray )                                                    \
        {                                                                              \
        }                                                                              \
        bCConstIterator( T const * _p, int _i ) :                                    \
            m_iIndex( _i ),                                                            \
            m_pArray( const_cast< T * >( _p ) )                                        \
        {                                                                              \
        }                                                                              \
        bCConstIterator( void ) :                                                      \
            m_iIndex( 0 ),                                                             \
            m_pArray( 0 )                                                              \
        {                                                                              \
        }                                                                              \
    };                                                                                 \
    class bCIterator :                                                                 \
        public bCConstIterator                                                         \
    {                                                                                  \
    public:                                                                            \
        T & operator * ( void ) const                                                  \
        {                                                                              \
            return this->m_pArray[ this->m_iIndex ];                                   \
        }                                                                              \
        T & operator [] ( int _n ) const                                             \
        {                                                                              \
            return this->m_pArray[ this->m_iIndex + _n ];                              \
        }                                                                              \
        bCIterator operator ++ ( int )                                               \
        {                                                                              \
            bCIterator _x = *this;                                                     \
            ++*this;                                                                   \
            return _x;                                                                 \
        }                                                                              \
        bCIterator & operator ++ ( void )                                              \
        {                                                                              \
            this->m_iIndex++;                                                          \
            return *this;                                                              \
        }                                                                              \
        bCIterator operator -- ( int )                                               \
        {                                                                              \
            bCIterator _x = *this;                                                     \
            --*this;                                                                   \
            return _x;                                                                 \
        }                                                                              \
        bCIterator & operator -- ( void )                                              \
        {                                                                              \
            this->m_iIndex--;                                                          \
            return *this;                                                              \
        }                                                                              \
        bCIterator & operator += ( int _n )                                          \
        {                                                                              \
            this->m_iIndex += _n;                                                      \
            return *this;                                                              \
        }                                                                              \
        bCIterator & operator -= ( int _n )                                          \
        {                                                                              \
            this->m_iIndex -= _n;                                                      \
            return *this;                                                              \
        }                                                                              \
        bCIterator operator + ( int _n ) const                                       \
        {                                                                              \
            bCIterator _x = *this;                                                     \
            return _x += _n;                                                           \
        }                                                                              \
        bCIterator operator - ( int _n ) const                                       \
        {                                                                              \
            bCIterator _x = *this;                                                     \
            return _x -= _n;                                                           \
        }                                                                              \
        bCIterator operator - ( bCIterator const & _x ) const                          \
        {                                                                              \
            return (this->m_pArray + this->m_iIndex) - (_x.m_pArray + _x.m_iIndex);    \
        }                                                                              \
        bool operator == ( bCIterator const & _x ) const                             \
        {                                                                              \
            return (this->m_iIndex == _x.m_iIndex) && (this->m_pArray == _x.m_pArray); \
        }                                                                              \
        bool operator != ( bCIterator const & _x ) const                             \
        {                                                                              \
            return !(*this == _x);                                                     \
        }                                                                              \
        bool operator < ( bCIterator const & _x ) const                              \
        {                                                                              \
            return (this->m_pArray + this->m_iIndex) < (_x.m_pArray + _x.m_iIndex);    \
        }                                                                              \
        bool operator > ( bCIterator const & _x ) const                              \
        {                                                                              \
            return _x < *this;                                                         \
        }                                                                              \
        bool operator <= ( bCIterator const & _x ) const                             \
        {                                                                              \
            return !(_x < *this);                                                      \
        }                                                                              \
        bool operator >= ( bCIterator const & _x ) const                             \
        {                                                                              \
            return !(*this < _x);                                                      \
        }                                                                              \
        bCIterator( T * _p, int _i ) :                                               \
            bCConstIterator( _p, _i )                                                  \
        {                                                                              \
        }                                                                              \
        bCIterator( void )                                                             \
        {                                                                              \
        }                                                                              \
    };                                                                                 \
    typedef bCIterator bCRandomAccessIterator;                                         \
    typedef bCConstIterator bCConstRandomAccessIterator;

template< typename T >
class bTArrayBase
{
    GE_DECLARE_ARRAY_ITERATORS()
public:
    enum bEIndex
    {
        bEIndex_Invalid = 0xFFFFFFFFL
    };
protected:
    T *    m_pArray;
    size_t  m_u32Count;
    size_t  m_u32Capacity;
protected:
    static void STDCALL Copy( T * _d, T const * _s, int _n );
    static void STDCALL Delete( T * _e, int _n );
    static void STDCALL Move( T * _d, T const * _s, int _n );
    static void STDCALL New( T * _e, int _n );
protected:
    void Init( void );
private:
    bTArrayBase< T > & operator = ( bTArrayBase< T > const & );  // not defined
protected:
             bTArrayBase( bTArrayBase< T > const & _s );         // not defined
    explicit bTArrayBase( int _n );                            // not defined
             bTArrayBase( void );
            ~bTArrayBase( void );
public:
    T *             AccessArray( void );
    T &             AccessAt( int _i );
    bCConstIterator Begin( void ) const;
    bCIterator      Begin( void );
    T const *       GetArray( void ) const;
    T const &       GetAt( int _i ) const;
    void            GetAt( int _i, T & _e ) const;
    int           GetCapacity( void ) const;
    int           GetCount( void ) const;
    bCConstIterator End( void ) const;
    bCIterator      End( void );
    int           IndexOf( T const & _e ) const;
    bool          IsEmpty( void ) const;
public:
    T &       operator [] ( int _i );
    T const & operator [] ( int _i ) const;
};

#include "bArrayBase.inl"

#endif