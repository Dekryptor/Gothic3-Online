#ifndef _BCOBJECTREFBASE_H
#define _BCOBJECTREFBASE_H

class DLLIMPORT bCObjectRefBase : bCObjectBase
{
public:
	unsigned int GetReferenceCount( void ) const;
};

#endif