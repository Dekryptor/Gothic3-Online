#ifndef _BCPROPERTYID_H
#define _BCPROPERTYID_H

class DLLIMPORT bCPropertyID
{
public:
	void CreateFromString( const bCString & );
	bCString GetText( void ) const;
	bCString GetTextEx( void ) const;
	bool SetText( const bCString & );
	bool SetTextEx( const bCString & );
	void Destroy();
	
	bCPropertyID( void );
	bCPropertyID( const bCPropertyID & );
	bCPropertyID( const bCGuid & );
	~bCPropertyID( void );
};
#endif