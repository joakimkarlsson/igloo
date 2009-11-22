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

template <class T>
class TestFixture : public TestFixtureBase
{
public:     
 	vector<TestFunctor*> _testMethods;  
	
   void Run() 
   {  
	T t;                
	vector<TestFunctor*> testMethods;
	t.GetTests(testMethods);
	for(vector<TestFunctor*>::iterator it = testMethods.begin(); it != testMethods.end(); it++)
	{        
		TestFunctor* func = *it;
		(*func)();
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
void GetTests(vector<TestFunctor*>& tests) \
{     

#define RegisterMethod(method) \
tests.push_back(new method());
	
#define EndRegisterTestMethods() \
}
         
TestFixture(MyTestCase)
{      			
public:      
	RegisterTestMethods();                              
	RegisterMethod(Test1);
	RegisterMethod(Test2);
	EndRegisterTestMethods();

   	class Test1 : public TestFunctor
	{
	  void operator()()
	  {
		cout << "Running Test1" << endl;   	
	  }
    };   
    
	class Test2 : public TestFunctor
	{
	  void operator()()
	  {
		cout << "Running Test2" << endl;   	
	  }
    };
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