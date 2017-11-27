#ifndef _GUI_H
#define _GUI_H
#pragma warning( push )
enum gEGameMessageType
{
	TEXT_LIGHTBLUE,
	TEXT_PINK,
	TEXT_DARKGREEN,
	TEXT_BLUE,
	Unk1,
	Unk2
};
class DLLIMPORT GUI
{
public:
	bool PrintScreen_Debug( const bCString &, float );
	bool PrintGameMessage( const bCUnicodeString & , gEGameMessageType );
	bool PrintScreenEnd( void );
};
#pragma warning( pop )
DLLIMPORT_EXTC GUI gui;
#endif 