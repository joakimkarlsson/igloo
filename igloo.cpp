#include <iostream>
#include <map>    
#include <vector>    
#include <boost/preprocessor.hpp>
using namespace std;
                                           
class TestFixtureBase
{     
public:
	virtual void Run() = 0;    
};
          
#ifndef MAX_NUMBER_OF_TEST_METHODS   
  #define MAX_NUMBER_OF_TEST_METHODS 20
#endif

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
		#define REPEAT_SIGNATURE(z,n,name) name ## n (testMethods);
		BOOST_PP_REPEAT(MAX_NUMBER_OF_TEST_METHODS, REPEAT_SIGNATURE, GetTest)
		#undef REPEAT_SIGNATURE 
	}
     
	#define REPEAT_SIGNATURE(z,n,name) virtual void name ## n (TestMethods&) {}
	BOOST_PP_REPEAT(MAX_NUMBER_OF_TEST_METHODS, REPEAT_SIGNATURE, GetTest)
	#undef REPEAT_SIGNATURE
                    
};

class TestRunner
{
public:
	typedef map<string, TestFixtureBase* > TestFixtureMap;
	static TestFixtureMap FixtureMap;
		
  	static void RunAllTests()
  	{
 		for(TestFixtureMap::iterator it = FixtureMap.begin(); it != FixtureMap.end(); it++)
		{
			cout << "Running test fixture: " << (*it).first << endl;
			(*it).second->Run();
		}   
  	}
};
TestRunner::TestFixtureMap TestRunner::FixtureMap;

int RegisterTestFixture(string name, TestFixtureBase* testFixture)
{        
	TestRunner::FixtureMap[name] = testFixture; 
	return 0;
}  

#define TestFixture(fixture) \
class fixture; \
int fixture##_dummy = RegisterTestFixture( #fixture , new TestFixture<fixture>()); \
class fixture : public TestFixture<fixture>            
                     
#define TestMethod(fixture, method) \
void BOOST_PP_CAT(GetTest, __COUNTER__)(vector< void (fixture::*)() >& tests) \
{ \
	tests.push_back(&fixture::method); \
} \
void method() 

TestFixture(MyTestCase)
{      			
public:      

	TestMethod(MyTestCase, Test1)
    {
		cout << "  Running Test1!" << endl;   	
    }

 	TestMethod(MyTestCase, Test2)
	{
		cout << "  Running Test2!" << endl;   	
	}
};

int main()
{      
	TestRunner::RunAllTests();
	
	return 0;
}