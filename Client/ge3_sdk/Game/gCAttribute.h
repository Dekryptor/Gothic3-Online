#ifndef _GCATTRIBUTE_H
#define _GCATTRIBUTE_H
class bPropertyObjectBase; //Temp
class DLLIMPORT gCAttribute
{
public:
	gCAttribute( const gCAttribute & );
	gCAttribute( void );
	
	void SetTag( const bCString & );
	void SetModifier( const int & );
	void SetBaseValue( const int & );
	virtual void ApplyDefaults( void );
	virtual int GetValue( void );
	virtual int GetMaximum( void );
	virtual void SetValue( int );
	
	
	//static bCPropertyObjectBase * STDCALL GetRootObject( void ) const;
	
};
#endif