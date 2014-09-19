#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


#include <Analyser/SymbolTable.h>


class boundingBox
{

public:
	boundingBox(int top, int bottom, int left, int right,void *obj);
	bool hitsPosition(int x, int y);
	void *mObj;

private:
	int mTop;
	int mLeft;
	int mRight;
	int mBottom;

};


#endif
