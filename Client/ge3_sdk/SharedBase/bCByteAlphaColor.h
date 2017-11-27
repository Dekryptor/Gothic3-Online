#ifndef _BCBYTEALPHACOLOR_H
#define _BCBYTEALPHACOLOR_H
class DLLIMPORT bCByteAlphaColor
{
public:
	bCByteAlphaColor( void );
	~bCByteAlphaColor( void );
	bCByteAlphaColor( unsigned char, unsigned char, unsigned char, unsigned char );
	void SetColor(unsigned char, unsigned char, unsigned char, unsigned char);
};
#endif