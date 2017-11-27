#ifndef _ECGUIMODULE_H
#define _ECGUIMODULE_H
class eCGUIAdmin;
class DLLIMPORT eCGUIModule
{
public:
	static eCGUIModule& STDCALL GetInstance();
	void EnableInput( bool );
	eCGUIAdmin& GetAdmin( void );
};
#endif