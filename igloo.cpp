#include <map>    
#include <vector>
using namespace std;
 

class TestFixtureFactory
{
};  
                                          
class TestFixtureBase
{     
public:
	virtual void Run() = 0;
	virtual void RegisterTestMethods() {}      
};
   
class TestFunctor
{
public:
	virtual void operator()() = 0;     
};

template <typename T>
class TestFixture : public TestFixtureBase
{
public:     
 	vector<TestFunctor*> _testMethods;  
	
   void Run() 
   {  
	T t;                
	vector<void (T::*)() > testMethods;
	typename vector<void (T::*)() >::iterator it;
	t.GetTests(testMethods);
	for(it = testMethods.begin(); it != testMethods.end(); it++)
	{        
	   void (T::*method)() = *it;
	   (t.*method)();
	}
   }     
};

typedef map<string, TestFixtureBase* > TestFixtureMap;
TestFixtureMap fixtureMap;

int RegisterTestFixture(string name, TestFixtureBase* testFixture)
{        
	fixtureMap[name] = testFixture; 
	testFixture->RegisterTestMethods();
	return 0;
}  

#define TestFixture(fixture) \
class fixture; \
int fixture##_dummy = RegisterTestFixture( #fixture , new TestFixture<fixture>()); \
class fixture : public TestFixture<fixture>            
      
#define RegisterTestMethods() \
void GetTests(vector< void (MyTestCase::*)() >& tests) \
{     

#define RegisterMethod(method) \
tests.push_back(&MyTestCase::method);
	
#define EndRegisterTestMethods() \
}
         
TestFixture(MyTestCase)
{      			
public:      
	RegisterTestMethods();                              
	RegisterMethod(Test1);
	RegisterMethod(Test2);
	EndRegisterTestMethods();

    void Test1()
    {
		cout << "Running Test1" << endl;   	
    }
    
	void Test2()
	  {
		cout << "Running Test2" << endl;   	
	  }
};

int main()
{            
	cout << "Igloo" << endl; 

	
	for(TestFixtureMap::iterator it = fixtureMap.begin(); it != fixtureMap.end(); it++)
	{
		cout << "Running test: " << (*it).first << endl;
		(*it).second->Run();
	}
	
	return 0;
}