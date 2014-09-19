#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>
#include <../Analyser/Analyser.h>
#include <../Analyser/SymbolTable.h>
#include <iostream>

#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>

struct TestAnalyserFixture
{
	TestAnalyserFixture()
	{
		mAnalyser = new Analyser();
		mSymbols=mAnalyser->getTable();
	}

	~TestAnalyserFixture()
	{
		
		//delete mSymbols;
		//delete mAnalyser;
	}


	SymbolTable *mSymbols;
	Analyser* mAnalyser;
};

BOOST_FIXTURE_TEST_SUITE(SimpleDecl, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimpleDeclInt)
	{
		const char*msg = "int i = 0;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i")); 
		BOOST_CHECK_EQUAL(sizeof(int), mSymbols->getType(L"int")->mSize);
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(SimpleDeclFloat)
	{
		const char*msg = "float i = 0;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i"));
		BOOST_CHECK(err == 0);  
	}

	BOOST_AUTO_TEST_CASE(SimpleDeclDouble)
	{
		const char*msg = "double i = 0;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i")); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(SimpleDeclChar)
	{
		const char*msg = "char i = 'a';";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i")); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(SimpleDeclBool)
	{
		const char*msg = "bool i = true;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i")); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(TestContains)
	{
		const char*msg = "bool i = true;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(false == mSymbols->isOnStack(L"j")); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(MultipleDectBool)
	{
		const char*msg = "bool i,g = true;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i")); 
		BOOST_CHECK(true == mSymbols->isOnStack(L"g")); 
		BOOST_CHECK(err == 0); 
	}




BOOST_AUTO_TEST_SUITE_END()







BOOST_FIXTURE_TEST_SUITE(DeclList, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimpleDeclList)
	{
		const char*msg = "int i,j, *k;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i")); 
		BOOST_CHECK(true == mSymbols->isOnStack(L"j")); 
		BOOST_CHECK(true == mSymbols->isOnStack(L"k")); 
		BOOST_CHECK(err == 0); 
	}



BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(SimpleFailDecl, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(UnknownTypeFail)
	{
		const char*msg = "inta i = 0;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0); 
	}

	BOOST_AUTO_TEST_CASE(MissingSemicolonFail)
	{
		const char*msg = "float i = 0";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0);
	}

	BOOST_AUTO_TEST_CASE(MissingAssignmentFail)
	{	
		const char*msg = "double i 0;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0); 
	}


BOOST_AUTO_TEST_SUITE_END()





BOOST_FIXTURE_TEST_SUITE(TypeAssignment, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(IntCharAssignmentFail)
	{
		const char*msg = "int i = 'a';";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0);  
	}


	BOOST_AUTO_TEST_CASE(IntFloatAssignmentFail)
	{
		const char*msg = "int i = 9.8;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0);  
	}


	BOOST_AUTO_TEST_CASE(VectorAssignmentFail)
	{
		const char*msg = "std::vector<int> *i = new std::vector<bool>;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0);  
	}

	BOOST_AUTO_TEST_CASE(VectorAssignmentPointerFail)
	{
		const char*msg = "std::vector<int> *i = new std::vector<int*>;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0);  
	}

	BOOST_AUTO_TEST_CASE(VectorAssignmentPointer2Fail)
	{
		const char*msg = "std::vector<int**> *i = new std::vector<int*>;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0);  
	}




BOOST_AUTO_TEST_SUITE_END()





BOOST_FIXTURE_TEST_SUITE(STLTest, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimpleVectorDecl)
	{	
		std::vector<int> mVect;
		const char*msg = "std::vector<int> mVect;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"mVect")); 
		BOOST_CHECK_EQUAL(sizeof(mVect),mSymbols->getType(L"vector")->mSize);
		BOOST_CHECK(err == 0);  
	}


	BOOST_AUTO_TEST_CASE(SimpleListDecl)
	{	
		std::list<int> mVect;
		const char*msg = "std::list<int> mVect;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"mVect")); 
		BOOST_CHECK_EQUAL(sizeof(mVect),mSymbols->getType(L"list")->mSize); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(SimpleDequeDecl)
	{	
		std::deque<int> mVect;
		const char*msg = "std::deque<int> mVect;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"mVect")); 
		BOOST_CHECK_EQUAL(sizeof(mVect),mSymbols->getType(L"deque")->mSize);
		BOOST_CHECK(err == 0);  
	}

	BOOST_AUTO_TEST_CASE(SimpleQueueDecl)
	{	
		std::queue<int> mVect;
		const char*msg = "std::queue<int> mVect;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"mVect")); 
		BOOST_CHECK_EQUAL(sizeof(mVect),mSymbols->getType(L"queue")->mSize); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(SimpleStackDecl)
	{	
		std::stack<int> mVect;
		const char*msg = "std::stack<int> mVect;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"mVect")); 
		BOOST_CHECK_EQUAL(sizeof(mVect),mSymbols->getType(L"stack")->mSize); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(VectorArray)
	{
		const char*msg = "std::vector<int> *i = new std::vector<int>[4];";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err == 0);  
	}

BOOST_AUTO_TEST_SUITE_END()



BOOST_FIXTURE_TEST_SUITE(StructTest, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimpleStructDecl)
	{	
		struct testStruct
		{
			int a;
			int b;
		}; 
		

		const char*msg = 
				"struct testStruct"
				"{"
				"	int a;"
				"	int b;"
				"}; "
				"testStruct myStruct;";

		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"myStruct")); 
		BOOST_CHECK(sizeof(testStruct) == mSymbols->getType(L"testStruct")->mSize); 
		BOOST_CHECK(err == 0); 
	}


	BOOST_AUTO_TEST_CASE(STLStructDecl)
	{	
		struct testStruct
		{
			std::vector<int> i;
			int b;
		}; 
		

		const char*msg = 
				"struct testStruct"
				"{"
				"	std::vector<int> i;"
				"	int b;"
				"}; "
				"testStruct myStruct;";

		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"myStruct")); 
		BOOST_CHECK(sizeof(testStruct) == mSymbols->getType(L"testStruct")->mSize); 
		BOOST_CHECK(err == 0); 
	}


	BOOST_AUTO_TEST_CASE(StructInStruct)
	{	
		struct testStruct
		{
			int i;
			int b;
		}; 
		

		struct testStruct2
		{
			int d;
			testStruct theTestStruct;
		}; 

		const char*msg = 
		"struct testStruct"
		"{"
		"	int i;"
		"	int b;"
		"}; "
		"struct testStruct2"
		"{"
		"	int d;"
		"	testStruct theTestStruct;"
		"}; " 
		"testStruct2 myStruct;";
	
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"myStruct")); 
		BOOST_CHECK(sizeof(testStruct2) == mSymbols->getType(L"testStruct2")->mSize); 
		BOOST_CHECK(err == 0); 
	}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(PredefinitionTest, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimplePredefinitionTest)
	{	
		struct pNode
		{
			pNode *left;
		}; 
		

		const char*msg = 
		"struct pNode"
		"{"
		"	pNode *left;"
		"};" ;

		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(sizeof(pNode) == mSymbols->getType(L"pNode")->mSize); 
		BOOST_CHECK(err == 0); 
	}

	
	BOOST_AUTO_TEST_CASE(SimplePredefinitionTestFail)
	{	
		const char*msg = 
		"struct pNode"
		"{"
		"	NoNode *left;"
		"};" ;

		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0); 
	}


BOOST_AUTO_TEST_SUITE_END()




BOOST_FIXTURE_TEST_SUITE(UnionTest, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimpleUnionDecl)
	{	
		union tUnion
		{
			int    mA;
			double mB;
		}; 
		

		const char*msg = 
			"union tUnion"
			"{"
			"	int    mA;"
			"	double mB;"
			"};"

			"tUnion theUnion;";

		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"theUnion")); 
		BOOST_CHECK(sizeof(tUnion) == mSymbols->getType(L"tUnion")->mSize); 
		BOOST_CHECK(err == 0); 
	}


BOOST_AUTO_TEST_SUITE_END()






BOOST_FIXTURE_TEST_SUITE(ClassTest, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimpleClassDecl)
	{	
		class testClass
		{
			int a;
			int b;
		}; 
		

		const char*msg = 
				"class testClass"
				"{"
				"	int a;"
				"	int b;"
				"}; "
				"testClass myClass;";

		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"myClass")); 
		BOOST_CHECK(sizeof(testClass) == mSymbols->getType(L"testClass")->mSize); 
		BOOST_CHECK(err == 0); 
	}


	BOOST_AUTO_TEST_CASE(InheritanceClassDecl)
	{	
		class firstClass
		{
			int a;
			int b;
		}; 

		class secondClass : public firstClass
		{
			int c;
			int d;
		}; 
		
		

		const char*msg = 
				"class firstClass"
				"{"
				"	int a;"
				"	int b;"
				"}; "

				"class secondClass : public firstClass"
				"{"
				"	int c;"
				"	int d;"
				"}; "
				""
				"secondClass myClass;";
		
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"myClass")); 
		BOOST_CHECK_EQUAL(sizeof(secondClass) , mSymbols->getType(L"secondClass")->mSize); 
		BOOST_CHECK(err == 0); 
	}




	
	BOOST_AUTO_TEST_CASE(MultipleInheritanceClassDecl)
	{	
		class firstClass
		{
			int a;
			int b;
		}; 
		
		class thirdClass
		{
			int a;
			int b;
		}; 

		class secondClass : public firstClass,thirdClass
		{
			int c;
			int d;
		}; 
		
		

		const char*msg = 

				"class thirdClass"
				"{"
				"	int a;"
				"	int b;"
				"}; "

				"class firstClass"
				"{"
				"	int a;"
				"	int b;"
				"}; "

				"class secondClass : public firstClass,thirdClass"
				"{"
				"	int c;"
				"	int d;"
				"}; "
				""
				"secondClass myClass;";
		
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"myClass")); 
		BOOST_CHECK_EQUAL(sizeof(secondClass) , mSymbols->getType(L"secondClass")->mSize);
		BOOST_CHECK(err == 0);  
	}


BOOST_AUTO_TEST_SUITE_END()



BOOST_FIXTURE_TEST_SUITE(PointerTest, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimplePointerDecl)
	{	
		const char*msg = "int *i;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i")); 
		BOOST_CHECK(err == 0); 
	}


	BOOST_AUTO_TEST_CASE(MultiPointerDecl)
	{	
		const char*msg = "int **i;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isOnStack(L"i")); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(NoPointerNewFail)
	{	
		const char*msg = "int i = new int;";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(err != 0); 
	}

	

BOOST_AUTO_TEST_SUITE_END()



BOOST_FIXTURE_TEST_SUITE(EnumeratorTest, TestAnalyserFixture)

	BOOST_AUTO_TEST_CASE(SimpleEnumeratorTest)
	{	
		const char*msg = "enum Farbe {ROT, GELB, GRUEN, BLAU};";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isDefined(L"Farbe")); 
		BOOST_CHECK(sizeof(int) == mSymbols->getType(L"Farbe")->mSize); 
		BOOST_CHECK(err == 0); 
	}

	BOOST_AUTO_TEST_CASE(AssignEnumeratorTest)
	{	
		const char*msg = "enum Farbe {ROT=2, GELB, GRUEN=7, BLAU};";
		int err = mAnalyser->compile((const unsigned char*)msg,strlen(msg));
		BOOST_CHECK(true == mSymbols->isDefined(L"Farbe")); 
		BOOST_CHECK(sizeof(int) == mSymbols->getType(L"Farbe")->mSize);
		BOOST_CHECK(err == 0);  
	}

BOOST_AUTO_TEST_SUITE_END()












