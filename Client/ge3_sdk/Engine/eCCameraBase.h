#ifndef _ECCAMERABASE_H
#define _ECCAMERABASE_H
class DLLIMPORT eCCameraBase
{
public:
	eCCameraBase(const eCCameraBase &);
	void WorldToScreen(bCVector &) const;
	void ScreenToWorld(bCVector &) const;
};
#endif