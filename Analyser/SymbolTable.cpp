#include "SymbolTable.h"
#include "Scanner.h"
#include "Parser.h"


#include <algorithm>



SymbolTable::SymbolTable()
{
	addDefinitions();
	StackPos = 0;
	HeapPos = 0;
	mPreDefine = 0;
}


SymbolTable::~SymbolTable()
{
	Clear();
}


void SymbolTable::ErrLine(size_t line,const wchar_t*msg){
	mErrorLines.push_back(line);
	mErrorMessages[line] =  coco_string_create(msg);
}

void SymbolTable::addDefinitions()
{
	define(L"int"          ,sizeof(int),   alignof(int)    );
	define(L"float"        ,sizeof(float), alignof(float)  );
	define(L"bool"         ,sizeof(bool),  alignof(bool)   );
	define(L"char"         ,sizeof(char),  alignof(char)   );
	define(L"double"       ,sizeof(double),alignof(double) );
	define(L"long"         ,sizeof(long),  alignof(long)   );
	define(L"wchar_t"      ,sizeof(wchar_t),  alignof(wchar_t)   );
	define(L"long double"  ,sizeof(long double),  alignof(long double)   );
	define(L"long long"    ,sizeof(long long),  alignof(long long)   );
	define(L"short"        ,sizeof(short), alignof(short)  );
	define(L"void"         ,sizeof(char),  alignof(char)   );
	define(L"signed"       ,sizeof(signed),  alignof(signed)   );
	define(L"unsigned"     ,sizeof(unsigned),  alignof(unsigned)   );
	define(L"vector"       ,sizeof(std::vector<int>), alignof(std::vector<int>) );
	define(L"list"         ,sizeof(std::list<int>), alignof(std::list<int>) );
	define(L"queue"        ,sizeof(std::queue<int>), alignof(std::queue<int>) );
	define(L"deque"        ,sizeof(std::deque<int>), alignof(std::deque<int>) );
	define(L"stack"        ,sizeof(std::stack<int>), alignof(std::stack<int>) );
	define(L"array"        ,sizeof(std::array<int,4>), alignof(std::array<int,4>) );
	define(L"string"        ,sizeof(std::string), alignof(std::string) );
	//define(L"set"        ,sizeof(std::set<int>), alignof(std::set<int>) );
	//define(L"map"        ,sizeof(std::map<int,int>), alignof(std::map<int,int>) )
	//define(L"std::multiset"  ,sizeof(std::set<int>), alignof(std::set<int>) );
	//define(L"std::multimap" ,sizeof(std::set<int>), alignof(std::set<int>) );
}


std::list<Declaration*> * SymbolTable::getStack()
{
	return &mStack;
}


std::list<Declaration*> * SymbolTable::getHeap()
{
	return &mHeap;
}


std::list<DataType*> *SymbolTable::getDefinitions()
{
	return &mDefinitions;
}

void SymbolTable::Clear()
{
	for (auto it = mStack.begin(); it != mStack.end(); it++)
	{	if(*it != 0){
			delete *it;
			*it = 0;
		}
	}

	for (auto it = mDefinitions.begin(); it != mDefinitions.end(); it++)
	{
		if(*it != 0){
			delete *it;
			*it = 0;
		}
	}

	for (auto it = mHeap.begin(); it != mHeap.end(); it++)
	{
		if(*it != 0){
			delete *it;	
			*it = 0;
		}
	}

	for(auto it = coco_strings.begin() ; it != coco_strings.end(); it++)
	{
		coco_string_delete(*it);
	}

	mStack.clear();
	mHeap.clear();
	mErrorLines.clear();
	mErrorMessages.clear();
	mDefinitions.clear();
	addDefinitions();
	StackPos = 0;
	HeapPos = 0;
}


bool SymbolTable::isDeclared( const wchar_t *name)
{
	if(name == 0)
		return false;

	if(isOnHeap(name) || isOnStack(name))
		return true;

	return false;
}


bool SymbolTable::isOnHeap( const wchar_t *name)
{
	if(name == 0)
		return false;

	for (auto it = mHeap.begin(); it != mHeap.end(); it++)
	{
		if (wcscmp ((*it)->mName,name) == 0)
			return true;
	}
	return false;

}
bool SymbolTable::isOnStack( const wchar_t *name)
{
	if(name == 0)
		return false;

	for (auto it = mStack.begin(); it != mStack.end(); it++)
	{
		if (wcscmp ((*it)->mName,name) == 0)
			return true;
	}
	return false;
}
	
size_t SymbolTable::getSizeOf( const wchar_t *name)
{
	if(name == 0){
		std::cerr << "getSizeOf: type zero pointer" << std::endl;
		return 102;
	}

	DataType * type = getType(name);

	if(type != 0){
		return type->mSize;
	} else { 
		std::cerr << "getSizeOf: type not found" << std::endl;
		return 101;
	}
}

bool SymbolTable::isDefined( const wchar_t *name)
{
	if(name == 0){
		std::cerr << "isDefined: zero pointer" << std::endl;
		return false;
	}


	if(0 == getType(name)){
		return false;
	} else {
		return true;
	}
}


void SymbolTable::define(const wchar_t *name , size_t size, size_t alignment)
{
	if(name == 0){
		std::cerr << "define: zero pointer" << std::endl;
		return;
	}

	mDefinitions.push_back(new DataType(name,size,alignment));
}

void SymbolTable::define(DataType *pDataType)
{
	if (pDataType == 0){
		std::cerr << "define: zero pointer" << std::endl;
		return;
	}

	mDefinitions.push_back(pDataType);
}

void SymbolTable::declareStack(Declaration *pObj)
{
	if(pObj == 0){
		std::cerr << "declareStack: zero pointer" << std::endl;
		return;
	}

	Declaration* padding = getPadding(StackPos,getAlignmentBoundary(pObj->mType));
	if(padding != 0){
		mStack.push_back(padding);
		StackPos += padding->mSize;
	}

	mStack.push_back(pObj);
	StackPos += pObj->mSize;
}

void SymbolTable::declareHeap(Declaration *pObj)
{
	if(pObj == 0){
		std::cerr << "declareHeap: zero pointer" << std::endl;
		return;
	}
	
	Declaration* padding = getPadding(HeapPos,getAlignmentBoundary(pObj->mType));
	if(padding != 0){
		mHeap.push_back(padding);
		HeapPos += padding->mSize;
	}

	mHeap.push_back(pObj);
	HeapPos += pObj->mSize;
}


Declaration *getPadding(size_t position, size_t alignmentBoundary)
{
	if(alignmentBoundary == 0){
		alignmentBoundary = 1;
	}

	if ((position % alignmentBoundary) == 0)
		return 0;	//Already Aligned

	size_t paddingSize =  alignmentBoundary - (position % alignmentBoundary);
	Declaration *paddingObject = new Declaration(L"padding",L"padding",paddingSize ,-1,0);
	return paddingObject;
}



size_t SymbolTable::getAlignmentBoundary(const wchar_t *name)
{
	if(name == 0){
		std::cerr << "getAlignmentBoundary: Zero Pointer" << std::endl;
		return 0;
	}

	DataType *type = getType(name);
	if(type != 0){
		return type->mAlignmentBoundary;
	} else {
		return 1;
	}
	
}


DataType *SymbolTable::getType(const wchar_t *type)
{
	if(type == 0){
		std::cerr << "getType: Zero Pointer" << std::endl;
		return 0;
	}

	for (auto it = mDefinitions.begin(); it != mDefinitions.end(); it++)
	{
		if (wcscmp ((*it)->mName,type) == 0){
			return (*it);
		}
	}

	return 0;
}


wchar_t *SymbolTable::string_create(wchar_t * val)
{
	wchar_t *str = coco_string_create(val);
	coco_strings.push_back(str);
	return str;
	//coco_string_delete
}







