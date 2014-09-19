#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <list>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <iostream>


#include "DataType.h"
#include "Declaration.h"


class Errors;
class DataType;



class SymbolTable
{
public:

	SymbolTable();
	~SymbolTable();
	void Err(wchar_t* msg);
	void ErrLine(size_t line,const wchar_t*msg);
	void Print();

	bool isDeclared( const wchar_t *name);
	bool isDefined( const wchar_t *name);
	
	bool isOnHeap( const wchar_t *name);
	bool isOnStack( const wchar_t *name);

	DataType *getType(const wchar_t *type);
	size_t getSizeOf( const wchar_t *name);
	
	size_t getAlignmentBoundary(const wchar_t *name);

	void Clear();

	std::list<Declaration*> * getStack();
	std::list<Declaration*> * getHeap();
	std::list<DataType*> * getDefinitions();

	void define(const wchar_t *name , size_t size, size_t alignment);
	void define(DataType *pDataType);

	void declareStack(Declaration *pObj);
	void declareHeap(Declaration *pObj);


	wchar_t *string_create(wchar_t * val);


	std::list<int> mErrorLines; //depraced
	std::map<int,wchar_t*> mErrorMessages;

	wchar_t *mPreDefine;
private: 
	void addDefinitions();
	std::list<Declaration*>  mStack;
	std::list<Declaration*>  mHeap;
	std::list<DataType*>     mDefinitions;
	int StackPos;
	int HeapPos;


	std::list<wchar_t*> coco_strings;



};


Declaration *getPadding(size_t position, size_t alignmentBoundary);




#endif
