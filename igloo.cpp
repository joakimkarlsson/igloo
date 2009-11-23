#include <iostream>
#include <map>    
#include <vector>
using namespace std;
                                           
class TestFixtureBase
{     
public:
	virtual void Run() = 0;    
};

template <typename T>
class TestFixture : public TestFixtureBase
{
public:        
	typedef void (T::*TestMethodPtr)(); 
	typedef vector<TestMethodPtr> TestMethods;
	 
   void Run() 
   {  
	T t;                
	TestMethods testMethods;
	t.GetTests(testMethods);   

	typename TestMethods::iterator it;
	
	for(it = testMethods.begin(); it != testMethods.end(); it++)
	{        
	   TestMethodPtr method = *it;
	   (t.*method)();
	}
   }           
   
	void GetTests(TestMethods& testMethods)
	{
		GetTest0(testMethods);
		GetTest1(testMethods);
		GetTest2(testMethods);
		GetTest3(testMethods);
		GetTest4(testMethods);
		GetTest5(testMethods);
		GetTest6(testMethods);
		GetTest7(testMethods);
		GetTest8(testMethods);
		GetTest9(testMethods);
		GetTest10(testMethods);
		GetTest11(testMethods);
		GetTest12(testMethods);
		GetTest13(testMethods);
		GetTest14(testMethods);
		GetTest15(testMethods);
		GetTest16(testMethods);
		GetTest17(testMethods);
		GetTest18(testMethods);
		GetTest19(testMethods);
		GetTest20(testMethods);
	}

   virtual void GetTest0(TestMethods&) { } 
   virtual void GetTest1(TestMethods&) { } 
   virtual void GetTest2(TestMethods&) { } 
   virtual void GetTest3(TestMethods&) { } 
   virtual void GetTest4(TestMethods&) { } 
   virtual void GetTest5(TestMethods&) { } 
   virtual void GetTest6(TestMethods&) { } 
   virtual void GetTest7(TestMethods&) { }
   virtual void GetTest8(TestMethods&) { }
   virtual void GetTest9(TestMethods&) { }
   virtual void GetTest10(TestMethods&) { }
   virtual void GetTest11(TestMethods&) { }
   virtual void GetTest12(TestMethods&) { }
   virtual void GetTest13(TestMethods&) { }
   virtual void GetTest14(TestMethods&) { }
   virtual void GetTest15(TestMethods&) { }
   virtual void GetTest16(TestMethods&) { }
   virtual void GetTest17(TestMethods&) { }
   virtual void GetTest18(TestMethods&) { }
   virtual void GetTest19(TestMethods&) { }
   virtual void GetTest20(TestMethods&) { }
 
};

typedef map<string, TestFixtureBase* > TestFixtureMap;
TestFixtureMap fixtureMap;

int RegisterTestFixture(string name, TestFixtureBase* testFixture)
{        
	fixtureMap[name] = testFixture; 
	return 0;
}  

#define TestFixture(fixture) \
class fixture; \
int fixture##_dummy = RegisterTestFixture( #fixture , new TestFixture<fixture>()); \
class fixture : public TestFixture<fixture>            
                     
#define APPENDCOUNTER_IMPL(x, l) x##l
#define APPENDCOUNTER_DETAIL(x, l) APPENDCOUNTER_IMPL(x, l)
#define APPENDCOUNTER(x) APPENDCOUNTER_DETAIL(x, __COUNTER__)


#define TestMethod(fixture, method) \
void APPENDCOUNTER(GetTest)(vector< void (fixture::*)() >& tests) \
{ \
	tests.push_back(&fixture::method); \
} \
void method() 

TestFixture(MyTestCase)
{      			
public:      

	TestMethod(MyTestCase, Test1)
    {
		cout << "  Running Test1" << endl;   	
    }

 	TestMethod(MyTestCase, Test2)
	{
		cout << "  Running Test2" << endl;   	
	}
};

int main()
{      
	for(TestFixtureMap::iterator it = fixtureMap.begin(); it != fixtureMap.end(); it++)
	{
		cout << "Running test fixture: " << (*it).first << endl;
		(*it).second->Run();
	}
	
	return 0;
}