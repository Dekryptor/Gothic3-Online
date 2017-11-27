#ifndef _BCSTRING_H
#define _BCSTRING_H
class DLLIMPORT bCString
{
protected:
	struct bSStringData
	{
		unsigned int m_u32Length;
		unsigned int m_u32RefCount;
		//GELPChar GetText( void );
	};
public:
	bCString( const bCString & );
	bCString( char, int );
	bCString( const char *, int );
	bCString( const char * );
	bCString( void );
	~bCString( void );
	
	
protected:
	void Decrement( void );
	void FreeData( void );
	bSStringData* GetData( void ) const;
public:
	bool CompareFast( const bCString & ) const;
	bool Contains( char, int ) const;
	bool Contains( const char *, int ) const;
	int STDCALL ContainsOneOf( char*, int );
	char* GetBuffer( int );
	char* GetBufferSetLength( int );
	char GetAt( int, bool ) const;
	void SetAt( int, char );
	void SetText( char, int );
	void SetText( const char * );
	void SetText( const char *, int );
	void SetText( const bCString & );
	void SetText( const bCString &, int );
	void Clear( void );
	bool CDECL Format( const char*, ... );
	void TrimLeft( void );
	void TrimLeft( char );
	void TrimLeft( const char * );
	void TrimRight( void );
	void TrimRight( char );
	void TrimRight( const char * );
	void Trim( void );
	void Trim( char );
	void Trim( const char * );
	void Trim( bool, bool );
	bCString & MakeUpper( void );
	bCString & MakeLower( void );
	int Replace(char, char);
	int Replace(const char*, const char*);
	void ToUpper( void );
	void ToLower( void );
	void MakeReverse( void );
	int Delete( int, int );
	int Insert( int, char );
	int Insert( int, const char * );
	int GetLength( void ) const;
	const char* GetText( void ) const;
	
	bCString & operator = ( char );
	bCString & operator = ( const char * );
	bCString & operator = ( const bCString & );
	bCString & operator += ( char );
	bCString & operator += ( const char * );
	bCString & operator += ( const bCString & );
	char operator[](int) const;
	char& operator[](int);
	bCString operator + ( const bCString & ) const;
	bCString operator + ( const char * ) const;
	bCString operator + ( char ) const;
	bool operator == ( const bCString & ) const;
	bool operator == ( const char * ) const;
	bool operator != ( const bCString & ) const;
	bool operator != ( const char * ) const;
	bool operator < ( const bCString & ) const;
	bool operator < ( const char * ) const;
	bool operator <= ( const bCString & ) const;
	bool operator <= ( const char * ) const;
	bool operator > ( const bCString & ) const;
	bool operator > ( const char * ) const;
	bool operator >= ( const bCString & ) const;
	bool operator >= ( const char * ) const;
	
	friend DLLIMPORT bool STDCALL operator == ( const char *, const bCString & );
	friend DLLIMPORT bool STDCALL operator != ( const char *, const bCString & );
	friend DLLIMPORT bool STDCALL operator < ( const char *, const bCString & );
	friend DLLIMPORT bool STDCALL operator <= ( const char *, const bCString & );
	friend DLLIMPORT bool STDCALL operator > ( const char *, const bCString & );
	friend DLLIMPORT bool STDCALL operator >= ( const char *, const bCString & );
	
};
#endif