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
	virtual void call() = 0;     
};

template <class T>
class TestFixture : public TestFixtureBase
{
public:     
 	vector<TestFunctor*> _testMethods;  
	
   void Run() 
   {  
	T t;                
	vector<TestFunctor*> testMethods = t.GetTestMethods();
	for(vector<TestFunctor*>::iterator it = testMethods.begin(); it != testMethods.end(); it++)
	{
		(*it)->call();
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
                                       
TestFixture(MyTestCase)
{      			
public:      
	
	class Test1 : public TestFunctor
	{
	  void call()
	  {
		cout << "Running Test1" << endl;   	
	  }
    };
	                                
	vector<TestFunctor*> GetTestMethods()
	{    
		vector<TestFunctor*> testMethods;
		testMethods.push_back(new Test1());
		return testMethods;
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