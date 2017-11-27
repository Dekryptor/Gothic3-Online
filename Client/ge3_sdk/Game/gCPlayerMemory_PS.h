#ifndef _GCPLAYERMEMORY_PS_H
#define _GCPLAYERMEMORY_PS_H
class DLLIMPORT gCPlayerMemory_PS :
	public eCEntityPropertySet
{	//For stats manipulation
public:
	bool SetValue(const bCString &, int);
	int GetValue(const bCString &) const;
	bool SetMaximum(const bCString &, int);
	int GetMaximum(const bCString &) const;
	void SetXP( const long & );
	void SetLPAttribs( const long & );
	void SetLPPerks( const long & );
	
};
#endif