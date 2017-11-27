#ifndef _BCUNICODESTRING_H
#define _BCUNICODESTRING_H
class DLLIMPORT bCUnicodeString
{
public:
	bCUnicodeString( const char* );
	bCUnicodeString( void );
	~bCUnicodeString( void );
	
	bCString GetAnsiText( void ) const;
	bCString GetAsHexCodedString( void ) const;
	void SetAnsiText( const bCString & );
};
#endif