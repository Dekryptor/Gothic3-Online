#ifndef _ECAPPLICATION_H
#define _ECAPPLICATION_H
class eCCameraBase;
class DLLIMPORT eCApplication
{
public:
	eCKeyboard& GetKeyboard( void );
	static eCApplication& STDCALL GetInstance( void );
	eCCameraBase& GetCurrentCamera( void ); //Coœ Ÿle znajduje kamere
	eCMouse& GetMouse( void );
};
#endif