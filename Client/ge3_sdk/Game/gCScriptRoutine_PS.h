#ifndef _GCSCRIPTROUTINE_PS_H
#define _GCSCRIPTROUTINE_PS_H
#pragma warning( push )
#pragma warning(disable:4273)
class DLLIMPORT gCScriptRoutine_PS : public eCEntityPropertySet
{
public:
	void SetCurrentTask( const bCString & );
}; 
#pragma warning( pop )
#endif