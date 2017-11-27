#ifndef _BCIOSTREAM_H
#define _BCIOSTREAM_H

class DLLIMPORT bCIOStream :
public bCIStream,
public bCOStream
{
public: 
	bCIOStream( class bCIOStream const & );
	bCIOStream( void );
	virtual ~bCIOStream( void );
};
#endif