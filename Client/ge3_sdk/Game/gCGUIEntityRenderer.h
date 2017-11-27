#ifndef _GCGUIENTITYRENDERER_H
#define _GCGUIENTITYRENDERER_H
class DLLIMPORT gCGUIEntityRenderer
{
public:
	gCGUIEntityRenderer( eCGUIAdmin* );
protected:
	bool CalcTextRect(const eCEntity*, const bCUnicodeString &, bCRect &, float &);
	bool IsFocus( eCEntity const* ) const;
};
#endif