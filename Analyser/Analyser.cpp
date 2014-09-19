#include "Analyser.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "Scanner.h"
#include <stdio.h>
#include <iostream>

Analyser::Analyser()
{
	mSymbolTable = new SymbolTable();
}
	
Analyser::~Analyser()
{
	if(mSymbolTable != 0)
		delete mSymbolTable;
}

SymbolTable *Analyser::getTable()
{
	return mSymbolTable;
}
	
int Analyser::compile(const unsigned char* buf, int len)
{	
	mSymbolTable->Clear();
	mScanner = new Scanner(buf,len);
	mParser = new Parser(mScanner);	
	mParser->tab = mSymbolTable;
	mParser->Parse();
	int count = mParser->errors->count;


	// Register Error Messages in Symbol Table
	for (auto it = mParser->errors->mErrorMessages.begin(); it != mParser->errors->mErrorMessages.end(); it++)
	{
		mSymbolTable->ErrLine(it->first,it->second);
	}

	delete mParser;
	delete mScanner;
	return count;
}

