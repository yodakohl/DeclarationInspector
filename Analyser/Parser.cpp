/*----------------------------------------------------------------------
Compiler Generator Coco/R,
Copyright (c) 1990, 2004 Hanspeter Moessenboeck, University of Linz
extended by M. Loeberbauer & A. Woess, Univ. of Linz
ported to C++ by Csaba Balazs, University of Szeged
with improvements by Pat Terry, Rhodes University

This program is free software; you can redistribute it and/or modify it 
under the terms of the GNU General Public License as published by the 
Free Software Foundation; either version 2, or (at your option) any 
later version.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
for more details.

You should have received a copy of the GNU General Public License along 
with this program; if not, write to the Free Software Foundation, Inc., 
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

As an exception, it is allowed to write an extension of Coco/R that is
used as a plugin in non-free software.

If not otherwise stated, any source code generated by Coco/R (other than 
Coco/R itself) does not fall under the GNU General Public License.
-----------------------------------------------------------------------*/


#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"




void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }
		if (la->kind == _asm_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _do_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _if_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _return_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _typedef_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _auto_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _inline_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _typeid_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _dynamic_cast_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _typename_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _else_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _sizeof_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _break_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _case_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _mutable_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _static_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _catch_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _explicit_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _namespace_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _static_cast_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _using_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _export_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _virtual_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _extern_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _operator_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _switch_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _template_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _volatile_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _const_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _const_cast_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _this_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _continue_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _for_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _throw_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _while_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _default_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _friend_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _register_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _delete_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _goto_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _reinterpret_cast_Keyword) {
				Err(L"Keyword not in Subset"); 
		}
		if (la->kind == _try_Keyword) {
				Err(L"Keyword not in Subset"); 
		}

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::CSub() {
		decllist decl; 
		while (StartOf(1)) {
			switch (la->kind) {
			case _ident: case 37 /* "std::vector" */: case 38 /* "std::list" */: case 39 /* "std::queue" */: case 40 /* "std::stack" */: case 41 /* "std::array" */: case 42 /* "std::deque" */: case 43 /* "std::string" */: case 44 /* "signed" */: case 45 /* "char" */: case 46 /* "short" */: case 47 /* "int" */: case 48 /* "double" */: case 49 /* "long" */: case 50 /* "unsigned" */: {
				simple_declaration(&decl);
				for (auto it : decl){tab->declareStack(it);} decl.clear(); 
				break;
			}
			case 30 /* "struct" */: {
				struct_definition();
				break;
			}
			case 34 /* "class" */: {
				class_definiton();
				break;
			}
			case 27 /* "enum" */: {
				enum_specifier();
				break;
			}
			case 36 /* "union" */: {
				union_definition();
				break;
			}
			case 6 /* ";" */: {
				Get();
				break;
			}
			}
		}
}

void Parser::simple_declaration(decllist*decl) {
		wchar_t* type = 0; Declaration* tmpDecl ; 
		type_specifier(type);
		if( (!isPredefined(type)) && (!mustBeDefined(type)) ){Err(L"Type Not Defined"); return;} 
		declarator(tmpDecl,type);
		if(tmpDecl) decl->push_back(tmpDecl); 
		while (la->kind == 26 /* "," */) {
			Get();
			declarator(tmpDecl,type);
			if(tmpDecl) decl->push_back(tmpDecl); 
		}
		Expect(6 /* ";" */);
}

void Parser::struct_definition() {
		wchar_t* name = 0;  decllist decl; DataType *pStruct = 0; 
		Expect(30 /* "struct" */);
		Ident(name);
		mustNotBeDefined(name); tab->mPreDefine =  tab->string_create(name); 
		Expect(28 /* "{" */);
		pStruct = new DataType(name,0,0); 
		while (StartOf(2)) {
			simple_declaration(&decl);
			for (auto it : decl){addMember(pStruct,it);} decl.clear(); 
		}
		Expect(29 /* "};" */);
		finishAndDefine(pStruct); tab->mPreDefine = 0; 
}

void Parser::class_definiton() {
		decllist decl; DataType *pStruct = 0; 
		class_head(pStruct);
		Expect(28 /* "{" */);
		while (StartOf(3)) {
			if (StartOf(2)) {
				simple_declaration(&decl);
				for (auto it : decl){addMember(pStruct,it);} decl.clear(); 
			} else {
				access_specifier();
				Expect(35 /* ":" */);
			}
		}
		Expect(29 /* "};" */);
		finishAndDefine(pStruct); tab->mPreDefine = 0; 
}

void Parser::enum_specifier() {
		wchar_t* name = 0; 
		Expect(27 /* "enum" */);
		Ident(name);
		mustNotBeDefined(name); 
		Expect(28 /* "{" */);
		enumerator_definition();
		while (la->kind == 26 /* "," */) {
			Get();
			enumerator_definition();
		}
		Expect(29 /* "};" */);
		tab->define(name,tab->getSizeOf(L"int"),0); 
}

void Parser::union_definition() {
		wchar_t* name = 0;decllist decl; std::list<int> mSizes; 
		Expect(36 /* "union" */);
		Ident(name);
		mustNotBeDefined(name); 
		Expect(28 /* "{" */);
		simple_declaration(&decl);
		for (auto it : decl){mSizes.push_back(tab->getSizeOf(it->mType));} 
		while (StartOf(2)) {
			decl.clear(); 
			simple_declaration(&decl);
			for (auto it : decl){mSizes.push_back(tab->getSizeOf(it->mType));} 
		}
		Expect(29 /* "};" */);
		int size = *std::max_element(mSizes.begin(), mSizes.end());
		int alignment = 0;
		tab->define(name,size,alignment); 
		
}

void Parser::Ident(wchar_t* &name) {
		Expect(_ident);
		name =  tab->string_create(t->val); 
}

void Parser::literal(Declaration* &decl) {
		if (la->kind == _integer_literal) {
			Get();
			decl = new Declaration(L"int",L"int",tab->getSizeOf(L"int"),la->line,tab->getType(L"int")); 
		} else if (la->kind == 7 /* "true" */ || la->kind == 8 /* "false" */) {
			if (la->kind == 7 /* "true" */) {
				Get();
			} else {
				Get();
			}
			decl = new Declaration(L"bool",L"bool",tab->getSizeOf(L"bool"),la->line,tab->getType(L"bool")); 
		} else if (la->kind == _character_literal) {
			Get();
			decl = new Declaration(L"char",L"char",tab->getSizeOf(L"char"),la->line,tab->getType(L"char")); 
		} else if (la->kind == _string_literal) {
			Get();
			decl = new Declaration(L"string",L"string",tab->getSizeOf(L"string"),la->line,tab->getType(L"string"));
			addStringElements(t->val);
			
		} else if (la->kind == _floating_literal) {
			Get();
			decl = new Declaration(L"float",L"float",tab->getSizeOf(L"float"),la->line,tab->getType(L"float")); 
		} else SynErr(52);
}

void Parser::new_expression(Declaration* &decl) {
		wchar_t* type = 0; int line = 0; std::list<int> dimensions; 
		Expect(9 /* "new" */);
		type_specifier(type);
		line = la->line; 
		array_bracket(dimensions);
		if(type && tab->isDefined(type)){
		  Declaration *mObj = new Declaration(type,type,tab->getSizeOf(type)*getDimensionSize(&dimensions),line+1,tab->getType(type));
		  addArrayElements(mObj,&dimensions);
		  tab->declareHeap(mObj); 
		  decl = mObj;
		} else {
		  Err(L"Datatype not defined");
		  decl = 0;
		}
		
		if(globalTemplateName != 0){
		   addStlElements();
		   if(fullTemplateDeclaration != fullTemplateName)
		        Err(L"Template Types do not match");
		}
		
		
}

void Parser::type_specifier(wchar_t* &name) {
		if (StartOf(4)) {
			long_type(name);
		} else if (la->kind == _ident) {
			Ident(name);
		} else if (StartOf(5)) {
			stl_container(name);
			template_specifier();
		} else if (la->kind == 43 /* "std::string" */) {
			stl_string(name);
			mustBeDefined(name); 
		} else SynErr(53);
}

void Parser::array_bracket(intlist &dimensions) {
		int dim = 0;  
		while (la->kind == 10 /* "[" */) {
			Get();
			Expect(_integer_literal);
			swscanf(t->val, L"%d", &dim);  dimensions.push_back(dim); 
			Expect(11 /* "]" */);
		}
}

void Parser::assignment_operator() {
		switch (la->kind) {
		case 12 /* "=" */: {
			Get();
			break;
		}
		case 13 /* "*=" */: {
			Get();
			Err(L"Operator *=  not in Subset"); 
			break;
		}
		case 14 /* "/=" */: {
			Get();
			Err(L"Operator /=  not in Subset"); 
			break;
		}
		case 15 /* "%=" */: {
			Get();
			Err(L"Operator %=  not in Subset"); 
			break;
		}
		case 16 /* "+=" */: {
			Get();
			Err(L"Operator +=  not in Subset"); 
			break;
		}
		case 17 /* "-=" */: {
			Get();
			Err(L"Operator -=  not in Subset"); 
			break;
		}
		case 18 /* ">>=" */: {
			Get();
			Err(L"Operator >>= not in Subset"); 
			break;
		}
		case 19 /* "<<=" */: {
			Get();
			Err(L"Operator <<= not in Subset"); 
			break;
		}
		case 20 /* "&=" */: {
			Get();
			Err(L"Operator &=  not in Subset"); 
			break;
		}
		case 21 /* "^=" */: {
			Get();
			Err(L"Operator ^=  not in Subset"); 
			break;
		}
		case 22 /* "|=" */: {
			Get();
			Err(L"Operator |=  not in Subset"); 
			break;
		}
		default: SynErr(54); break;
		}
}

void Parser::declarator(Declaration*&tmpDecl, wchar_t*&type) {
		bool isPointer = false; int line = 0; std::list<int> dimensions; wchar_t* name = 0; 
		if (type == 0) {tmpDecl = 0; return; } 
		while (la->kind == 23 /* "*" */) {
			Get();
			isPointer = true;        
		}
		if(isPredefined(type) && isPointer == false) {Err(L"Predefinition only possible with pointers"); tmpDecl = 0; return; } 
		Ident(name);
		line = la->line; 
		array_bracket(dimensions);
		if(globalTemplateName != 0 ) { fullTemplateDeclaration = fullTemplateName; fullTemplateName.clear();  } 
		unary_expression(type,isPointer);
		if(isPointer){
		   tmpDecl = new Declaration(name,L"Pointer",sizeof(void*)*getDimensionSize(&dimensions),line+1,tab->getType(L"char"));
		   tmpDecl->setIsPointer(true);
		   addArrayElements(tmpDecl,&dimensions);
		} else {
		   tmpDecl = new Declaration(name,type,tab->getSizeOf(type)*getDimensionSize(&dimensions),line+1,tab->getType(type)); 
		   addArrayElements(tmpDecl,&dimensions);
		}
		
		// Add Elements to STL Container
		if(globalTemplateName != 0 && (isPointer == false)){
		   addStlElements();
		  
		}
		
		fullTemplateDeclaration.clear();
		fullTemplateName.clear();
		globalTemplateNamePointer = false;
		globalTemplateName = 0; 
		
}

void Parser::unary_expression(wchar_t*&type ,bool isPointer) {
		Declaration *assignmentType; 
		if (StartOf(6)) {
			assignment_operator();
			if (StartOf(7)) {
				literal(assignmentType);
				if(!typeMatch(type, assignmentType)){Err(L"Type Mismatch");} 
			} else if (la->kind == 9 /* "new" */) {
				new_expression(assignmentType);
				if(isPointer == false){Err(L"Pointer Required "); return;}  
				if(!typeMatch(type, assignmentType)){Err(L"Type Mismatch");} 
			} else SynErr(55);
		}
}

void Parser::template_specifier() {
		wchar_t *templateName = 0; 
		fullTemplateName.clear(); 
		Expect(24 /* "<" */);
		type_specifier(templateName);
		if(templateName) fullTemplateName.append(templateName); 
		while (la->kind == 23 /* "*" */) {
			Get();
			globalTemplateNamePointer = true; fullTemplateName.append(L"*"); 
		}
		Expect(25 /* ">" */);
		globalTemplateName = templateName; 
		mustBeDefined(templateName); 
}

void Parser::long_type(wchar_t* &name) {
		if (StartOf(8)) {
			if (la->kind == 44 /* "signed" */) {
				Get();
			}
			if (la->kind == 45 /* "char" */) {
				Get();
				name =  tab->string_create(L"char"); 
			} else if (la->kind == 46 /* "short" */) {
				Get();
				if (la->kind == 47 /* "int" */) {
					Get();
				}
				name =  tab->string_create(L"short"); 
			} else if (la->kind == 47 /* "int" */) {
				Get();
				name =  tab->string_create(L"int"); 
			} else if (la->kind == 48 /* "double" */) {
				Get();
				name =  tab->string_create(L"double"); 
			} else if (la->kind == 49 /* "long" */) {
				Get();
				if (StartOf(9)) {
					if (la->kind == 47 /* "int" */) {
						Get();
					}
					name =  tab->string_create(L"long"); 
				} else if (la->kind == 49 /* "long" */) {
					Get();
					if (la->kind == 47 /* "int" */) {
						Get();
					}
					name =  tab->string_create(L"long long"); 
				} else if (la->kind == 48 /* "double" */) {
					Get();
					name =  tab->string_create(L"long double"); 
				} else SynErr(56);
			} else SynErr(57);
		} else if (la->kind == 50 /* "unsigned" */) {
			Get();
			if (la->kind == 45 /* "char" */) {
				Get();
				name =  tab->string_create(L"char"); 
			} else if (la->kind == 46 /* "short" */) {
				Get();
				Expect(47 /* "int" */);
				name =  tab->string_create(L"short"); 
			} else if (la->kind == 47 /* "int" */) {
				Get();
				name =  tab->string_create(L"int"); 
			} else if (la->kind == 49 /* "long" */) {
				Get();
				if (la->kind == 47 /* "int" */) {
					Get();
					name =  tab->string_create(L"long"); 
				} else if (la->kind == 49 /* "long" */) {
					Get();
					Expect(47 /* "int" */);
					name =  tab->string_create(L"long long"); 
				} else SynErr(58);
			} else SynErr(59);
		} else SynErr(60);
}

void Parser::stl_container(wchar_t* &name) {
		switch (la->kind) {
		case 37 /* "std::vector" */: {
			Get();
			name =  tab->string_create(L"vector");  
			break;
		}
		case 38 /* "std::list" */: {
			Get();
			name =  tab->string_create(L"list");    
			break;
		}
		case 39 /* "std::queue" */: {
			Get();
			name =  tab->string_create(L"queue");   
			break;
		}
		case 40 /* "std::stack" */: {
			Get();
			name =  tab->string_create(L"stack");   
			break;
		}
		case 41 /* "std::array" */: {
			Get();
			name =  tab->string_create(L"array");   
			break;
		}
		case 42 /* "std::deque" */: {
			Get();
			name =  tab->string_create(L"deque");   
			break;
		}
		default: SynErr(61); break;
		}
}

void Parser::stl_string(wchar_t* &name) {
		Expect(43 /* "std::string" */);
		name =  tab->string_create(L"string");  
}

void Parser::enumerator_definition() {
		wchar_t* name = 0;  Declaration* decl = 0;  
		Ident(name);
		if (la->kind == 12 /* "=" */) {
			Get();
			literal(decl);
			if(decl && (wcscmp((decl)->mType,L"int") != 0)) {Err(L"Must be Integer");} 
		}
}

void Parser::access_specifier() {
		if (la->kind == 31 /* "public" */) {
			Get();
		} else if (la->kind == 32 /* "private" */) {
			Get();
		} else if (la->kind == 33 /* "protected" */) {
			Get();
		} else SynErr(62);
}

void Parser::class_head(DataType *&pStruct) {
		wchar_t* name = 0;  wchar_t* baseclass = 0; 
		Expect(34 /* "class" */);
		Ident(name);
		if(mustNotBeDefined(name)){pStruct = new DataType(name,0,0);}  tab->mPreDefine =  tab->string_create(name);  
		if (la->kind == 35 /* ":" */) {
			Get();
			if (la->kind == 31 /* "public" */ || la->kind == 32 /* "private" */ || la->kind == 33 /* "protected" */) {
				access_specifier();
			}
			Ident(baseclass);
			inherit(pStruct,baseclass); 
			while (la->kind == 26 /* "," */) {
				Get();
				Ident(baseclass);
				inherit(pStruct,baseclass); 
			}
		}
}




// If the user declared a method Init and a mehtod Destroy they should
// be called in the contructur and the destructor respctively.
//
// The following templates are used to recognize if the user declared
// the methods Init and Destroy.

template<typename T>
struct ParserInitExistsRecognizer {
	template<typename U, void (U::*)() = &U::Init>
	struct ExistsIfInitIsDefinedMarker{};

	struct InitIsMissingType {
		char dummy1;
	};
	
	struct InitExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static InitIsMissingType is_here(...);

	// exist only if ExistsIfInitIsDefinedMarker is defined
	template<typename U>
	static InitExistsType is_here(ExistsIfInitIsDefinedMarker<U>*);

	enum { InitExists = (sizeof(is_here<T>(NULL)) == sizeof(InitExistsType)) };
};

template<typename T>
struct ParserDestroyExistsRecognizer {
	template<typename U, void (U::*)() = &U::Destroy>
	struct ExistsIfDestroyIsDefinedMarker{};

	struct DestroyIsMissingType {
		char dummy1;
	};
	
	struct DestroyExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static DestroyIsMissingType is_here(...);

	// exist only if ExistsIfDestroyIsDefinedMarker is defined
	template<typename U>
	static DestroyExistsType is_here(ExistsIfDestroyIsDefinedMarker<U>*);

	enum { DestroyExists = (sizeof(is_here<T>(NULL)) == sizeof(DestroyExistsType)) };
};

// The folloing templates are used to call the Init and Destroy methods if they exist.

// Generic case of the ParserInitCaller, gets used if the Init method is missing
template<typename T, bool = ParserInitExistsRecognizer<T>::InitExists>
struct ParserInitCaller {
	static void CallInit(T *t) {
		// nothing to do
	}
};

// True case of the ParserInitCaller, gets used if the Init method exists
template<typename T>
struct ParserInitCaller<T, true> {
	static void CallInit(T *t) {
		t->Init();
	}
};

// Generic case of the ParserDestroyCaller, gets used if the Destroy method is missing
template<typename T, bool = ParserDestroyExistsRecognizer<T>::DestroyExists>
struct ParserDestroyCaller {
	static void CallDestroy(T *t) {
		// nothing to do
	}
};

// True case of the ParserDestroyCaller, gets used if the Destroy method exists
template<typename T>
struct ParserDestroyCaller<T, true> {
	static void CallDestroy(T *t) {
		t->Destroy();
	}
};

void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	CSub();
	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 51;

	ParserInitCaller<Parser>::CallInit(this);
	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[10][53] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x},
		{x,T,x,x, x,x,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,x,T,x, x,x,T,x, T,T,T,T, T,T,T,T, T,T,T,T, T,T,T,x, x},
		{x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,T, T,T,T,T, T,T,T,T, T,T,T,x, x},
		{x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,T,x,x, x,T,T,T, T,T,T,T, T,T,T,T, T,T,T,x, x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,T,T,T, T,T,T,x, x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,T, T,T,T,x, x,x,x,x, x,x,x,x, x},
		{x,x,x,x, x,x,x,x, x,x,x,x, T,T,T,T, T,T,T,T, T,T,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x},
		{x,x,T,T, T,T,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,T,T,T, T,T,x,x, x},
		{x,T,x,x, x,x,T,x, x,x,T,x, x,x,x,x, x,x,x,x, x,x,x,T, x,T,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	ParserDestroyCaller<Parser>::CallDestroy(this);
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
	//mErrorMessages.clear();
}

void Errors::SynErr(int line, int col, int n) {
	
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"ident expected"); break;
			case 2: s = coco_string_create(L"string_literal expected"); break;
			case 3: s = coco_string_create(L"character_literal expected"); break;
			case 4: s = coco_string_create(L"floating_literal expected"); break;
			case 5: s = coco_string_create(L"integer_literal expected"); break;
			case 6: s = coco_string_create(L"\";\" expected"); break;
			case 7: s = coco_string_create(L"\"true\" expected"); break;
			case 8: s = coco_string_create(L"\"false\" expected"); break;
			case 9: s = coco_string_create(L"\"new\" expected"); break;
			case 10: s = coco_string_create(L"\"[\" expected"); break;
			case 11: s = coco_string_create(L"\"]\" expected"); break;
			case 12: s = coco_string_create(L"\"=\" expected"); break;
			case 13: s = coco_string_create(L"\"*=\" expected"); break;
			case 14: s = coco_string_create(L"\"/=\" expected"); break;
			case 15: s = coco_string_create(L"\"%=\" expected"); break;
			case 16: s = coco_string_create(L"\"+=\" expected"); break;
			case 17: s = coco_string_create(L"\"-=\" expected"); break;
			case 18: s = coco_string_create(L"\">>=\" expected"); break;
			case 19: s = coco_string_create(L"\"<<=\" expected"); break;
			case 20: s = coco_string_create(L"\"&=\" expected"); break;
			case 21: s = coco_string_create(L"\"^=\" expected"); break;
			case 22: s = coco_string_create(L"\"|=\" expected"); break;
			case 23: s = coco_string_create(L"\"*\" expected"); break;
			case 24: s = coco_string_create(L"\"<\" expected"); break;
			case 25: s = coco_string_create(L"\">\" expected"); break;
			case 26: s = coco_string_create(L"\",\" expected"); break;
			case 27: s = coco_string_create(L"\"enum\" expected"); break;
			case 28: s = coco_string_create(L"\"{\" expected"); break;
			case 29: s = coco_string_create(L"\"};\" expected"); break;
			case 30: s = coco_string_create(L"\"struct\" expected"); break;
			case 31: s = coco_string_create(L"\"public\" expected"); break;
			case 32: s = coco_string_create(L"\"private\" expected"); break;
			case 33: s = coco_string_create(L"\"protected\" expected"); break;
			case 34: s = coco_string_create(L"\"class\" expected"); break;
			case 35: s = coco_string_create(L"\":\" expected"); break;
			case 36: s = coco_string_create(L"\"union\" expected"); break;
			case 37: s = coco_string_create(L"\"std::vector\" expected"); break;
			case 38: s = coco_string_create(L"\"std::list\" expected"); break;
			case 39: s = coco_string_create(L"\"std::queue\" expected"); break;
			case 40: s = coco_string_create(L"\"std::stack\" expected"); break;
			case 41: s = coco_string_create(L"\"std::array\" expected"); break;
			case 42: s = coco_string_create(L"\"std::deque\" expected"); break;
			case 43: s = coco_string_create(L"\"std::string\" expected"); break;
			case 44: s = coco_string_create(L"\"signed\" expected"); break;
			case 45: s = coco_string_create(L"\"char\" expected"); break;
			case 46: s = coco_string_create(L"\"short\" expected"); break;
			case 47: s = coco_string_create(L"\"int\" expected"); break;
			case 48: s = coco_string_create(L"\"double\" expected"); break;
			case 49: s = coco_string_create(L"\"long\" expected"); break;
			case 50: s = coco_string_create(L"\"unsigned\" expected"); break;
			case 51: s = coco_string_create(L"??? expected"); break;
			case 52: s = coco_string_create(L"invalid literal"); break;
			case 53: s = coco_string_create(L"invalid type_specifier"); break;
			case 54: s = coco_string_create(L"invalid assignment_operator"); break;
			case 55: s = coco_string_create(L"invalid unary_expression"); break;
			case 56: s = coco_string_create(L"invalid long_type"); break;
			case 57: s = coco_string_create(L"invalid long_type"); break;
			case 58: s = coco_string_create(L"invalid long_type"); break;
			case 59: s = coco_string_create(L"invalid long_type"); break;
			case 60: s = coco_string_create(L"invalid long_type"); break;
			case 61: s = coco_string_create(L"invalid stl_container"); break;
			case 62: s = coco_string_create(L"invalid access_specifier"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	addMessage(line,s);
	coco_string_delete(s);
}


void Errors::addMessage(int line, const wchar_t *s)
{
	if(mErrorMessages.count(line) == 0){
		mErrorMessages[line] = coco_string_create(s);
	} else {

		wchar_t wcs[1024];
  		wcscpy (wcs,mErrorMessages[line]);
		wcscat(wcs,L"\n");
		wcscat(wcs,s);
		mErrorMessages[line] = coco_string_create(wcs);
	}
	count++;

}


void Errors::Error(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	addMessage(line,s);
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	wprintf(L"%ls", s); 
	exit(1);
}

