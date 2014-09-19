#include "Declaration.h"
#include "Scanner.h"
#include "Parser.h"

Declaration::Declaration(const wchar_t *name, const wchar_t *type,size_t size, int line, DataType *ptype) 
{

	if(name == 0 || type == 0 || ptype == 0){
		std::cerr << "Declaration::Declaration: zero pointer" << std::endl;
	}

	mName        = coco_string_create(name);
	mType        = coco_string_create(type);
	mLine        = line;
	mSize        = size;
	mDataType    = ptype;
	mIsPointer = false;
	mIsArray = false;
}

Declaration::~Declaration() {
	coco_string_delete(mName);
	coco_string_delete(mType);
}


void Declaration::setIsPointer(bool value)
{
	mIsPointer = value;
}

void Declaration::setIsArray(bool value)
{
	mIsArray = value;
}


void Declaration::addDetail(Declaration *mObj)
{
	if(mObj == 0){
		std::cerr << "Declaration::addDetail: zero pointer" << std::endl;
		return;
	}

	mDetail.push_back(mObj);
}
