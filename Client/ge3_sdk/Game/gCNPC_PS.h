#ifndef _GCNPC_PS
#define _GCNPC_PS
class DLLIMPORT gCNPC_PS
	: public eCEntityPropertySet
{
public:
	const bCString & GetCurrentMovementAni( void ) const;
	void SetCurrentMovementAni( const bCString & );
	void SetDescription( const bCString & );
};
#endif