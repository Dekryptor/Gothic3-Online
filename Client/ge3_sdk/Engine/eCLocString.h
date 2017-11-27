#ifndef _ECLOCSTRING_H
#define _ECLOCSTRING_H
class DLLIMPORT eCLocString
{
public:
	eCLocString(const bCString&);
	const bCUnicodeString GetString( void ) const;
};
#endif