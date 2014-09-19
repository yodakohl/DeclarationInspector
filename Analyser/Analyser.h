#ifndef ANALYSER_H
#define ANALYSER_H

#include "stdio.h"

#include <sys/timeb.h>
#include <wchar.h>


class Scanner;
class Parser ;
class SymbolTable;

class Analyser
{

public:
	Analyser();
	~Analyser();
	SymbolTable *getTable();
	int compile(const unsigned char* buf, int len);

private:

	Scanner *mScanner;
	Parser *mParser;
	SymbolTable *mSymbolTable;
};


#endif
