#ifndef _BCISTREAM_H
#define _BCISTREAM_H
class DLLIMPORT bCIStream
{
public:
	bCIStream( bCIStream const & );
	bCIStream( void );
	virtual ~bCIStream( void );
	
	virtual unsigned long Read(void* , unsigned long);
	unsigned long ReadLine( bCString & );
	unsigned long ReadLine( bCUnicodeString & );
	unsigned long Read( bool & );
	unsigned long Read( short & );
	unsigned long Read( int & );
	unsigned long Read( unsigned int & );
	unsigned long Read( long & );
	virtual unsigned long Read( bCString & );
	unsigned long Read( bCUnicodeString & );
	unsigned long Read( bCVariant & );
	unsigned long SkipBytes( unsigned long );
	
	bCIStream & operator >> ( unsigned char & );
	bCIStream & operator >> ( short & );
	bCIStream & operator >> ( long & );
	bCIStream & operator >> ( int & );
	bCIStream & operator >> ( unsigned int & );
	bCIStream & operator >> ( bCUnicodeString & );
	bCIStream & operator >> ( bCVariant & );
	//bCIStream & operator >> ( bCGUID & );
	
	friend DLLIMPORT bCIStream & STDCALL operator << ( unsigned char &, bCIStream & );
	friend DLLIMPORT bCIStream & STDCALL operator << ( unsigned short &, bCIStream & );
	friend DLLIMPORT bCIStream & STDCALL operator << ( int &, bCIStream & );
	friend DLLIMPORT bCIStream & STDCALL operator << ( unsigned int &, bCIStream & );
	friend DLLIMPORT bCIStream & STDCALL operator << ( float &, bCIStream & );
	friend DLLIMPORT bCIStream & STDCALL operator << ( bCUnicodeString &, bCIStream & );
	friend DLLIMPORT bCIStream & STDCALL operator << ( bCVariant &, bCIStream & );
};
#endif