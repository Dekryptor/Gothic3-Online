#ifndef _BCGUID_H
#define _BCGUID_H

class DLLIMPORT bCGuid
{
public:
	bCString GetText( void ) const;
	bool SetText( const bCString & );
};

#endif