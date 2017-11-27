#ifndef _GCGUIMANAGER_H
#define _GCGUIMANAGER_H
class DLLIMPORT gCGUIManager
{
public:
	bool ClearAllEntities( void );
	bool OpenMenu( void );
	bool CloseMenu( void );
	bool IsMenuOpen( void ) const;
	bool OpenInventory( void );

};
#endif