#include "boundingbox.h"

bool boundingBox::hitsPosition(int x, int y)
{
	if (y < mTop || y > mBottom || x < mLeft || x > mRight) 
		return false;

	return true;
}

boundingBox::boundingBox(int top, int bottom, int left, int right,void *obj)
{
	mTop = top;
	mBottom = bottom;
	mLeft = left;
	mRight = right;
	mObj = obj;
}
