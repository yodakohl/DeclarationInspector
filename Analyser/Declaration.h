#ifndef DECLARATION_H
#define DECLARATION_H

#include "DataType.h"
#include <iostream>
#include <list>
class DataType;

class Declaration 
{
public:

	Declaration(const wchar_t *name,const wchar_t *type,size_t size, int line, DataType *ptype);
	~Declaration();

	void addDetail(Declaration *mObj);
	void setIsPointer(bool value);
	void setIsArray(bool value);

	wchar_t* mName;		// name of the object
	wchar_t* mType;		// type of the object
	int mLine;			// Line number of declaration
	size_t mSize;		// Size of Declaration can be different of Type (Array)
	DataType *mDataType;
	std::list<Declaration*> mDetail;
	bool mIsPointer;
	bool mIsArray;
};


#endif
