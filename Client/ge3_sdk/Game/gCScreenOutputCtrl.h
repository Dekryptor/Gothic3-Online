#ifndef _GCSCRENOUTPUTCTRL_H
#define _GCSCRENOUTPUTCTRL_H
class DLLIMPORT gCScreenOutputCtrl
{
public:
	void PrintScreenEnd( void );
	void PrintScreen( const bCUnicodeString &, const bCByteAlphaColor &, float );
	void OutDebugEnd( bCString & );
};
#endif