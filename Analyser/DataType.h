#ifndef DATATYPE_H
#define DATATYPE_H

#include "Declaration.h"

#include <cstddef>
#include <list>

class Declaration;

class DataType{

public:

	DataType(const wchar_t *name, size_t size, size_t alignmentBoundary);
	~DataType();

	void addMember(Declaration* member);
	void finish();
	size_t getBiggestMember();
	size_t getBiggestMemberAlignment();
	wchar_t* mName;
	size_t mSize;
	size_t mAlignmentBoundary;
	std::list<Declaration*> mMembers;


	private:

	size_t mPointer; //Helps with Alignment
};

#endif
