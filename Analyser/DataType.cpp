#include "DataType.h"
#include "Scanner.h"
#include "Parser.h"

DataType::DataType(const wchar_t *name,size_t size, size_t alignmentBoundary)
{
	mName = coco_string_create(name);
	mAlignmentBoundary = alignmentBoundary;
	mSize = size;
	mPointer = 0;
}

DataType::~DataType()
{
	for (auto it = mMembers.begin(); it != mMembers.end(); it++)
	{	if(*it != 0){
			delete *it;
			*it = 0;
		}
	}
	coco_string_delete(mName);
}

void DataType::addMember(Declaration* member)
{
	if(member == 0)
		return;
	
	Declaration* padding = getPadding(mPointer,member->mDataType->mAlignmentBoundary);
	if(padding != 0){
		mMembers.push_back(padding);
		mPointer += padding->mSize;
		mSize += padding->mSize;
	}

	mMembers.push_back(member);
	mPointer += member->mSize;
	mSize += member->mSize;
}


size_t DataType::getBiggestMember()
{
	size_t tmpSize = 0;
	for(auto it = mMembers.begin(); it != mMembers.end(); it++)
	{	if (*it && (*it)->mDataType){
			size_t sizeNew = (*it)->mDataType->mSize;
			tmpSize = std::max(tmpSize,sizeNew);
		}
	}
	return tmpSize;
}

size_t DataType::getBiggestMemberAlignment()
{
	size_t tmpSize = 0;
	for(auto it = mMembers.begin(); it != mMembers.end(); it++)
	{	if (*it && (*it)->mDataType){
			size_t sizeNew = (*it)->mDataType->mAlignmentBoundary;
			tmpSize = std::max(tmpSize,sizeNew);
		}
	}
	return tmpSize;
}




void DataType::finish()
{
	Declaration* padding = getPadding(mPointer,getBiggestMemberAlignment());
	if(padding != 0){
		mMembers.push_back(padding);
		mPointer += padding->mSize;
		mSize += padding->mSize;
	}

	mAlignmentBoundary = getBiggestMember();
}


