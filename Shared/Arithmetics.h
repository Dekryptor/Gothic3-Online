#ifndef _ARITHMETICS_H
#define _ARITHMETICS_H
#include <math.h>
#define GetDistance3D(aX, aY, aZ, bX, bY, bZ)\
	sqrt((aX-bX)*(aX-bX)+(aY-bY)*(aY-bY)+(aZ-bZ)*(aZ-bZ))
#define GetDistance2D(aX, aY, bX, bY)\
	sqrt((aX-bX)*(aX-bX)+(aY-bY)*(aY-bY))
#define GetLerp(start, end, speed)\
	(start + (end-start)*speed)
#define Random(min, max)\
	(min + (int)((double)rand() / (RAND_MAX+1) * (max-min+1)))
#endif