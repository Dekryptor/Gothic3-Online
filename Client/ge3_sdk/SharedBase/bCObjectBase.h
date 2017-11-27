#ifndef _OBCBJECTBASE_H
#define _OBCBJECTBASE_H

enum bEDoNotOverwriteMethod
{
	bEDoNotOverwriteMethod_False = false,
	bEDoNotOverwriteMethod_Ok = true,
	bEDoNotOverwriteMethod_ForceDWORD = FORCE_DWORD
};

class DLLIMPORT bCObjectBase
{
public:
	bCString const & GetClassName( void ) const;
};

#endif