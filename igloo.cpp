#include <map>    

using namespace std;
 

class TestFixtureFactory
{
};  
                                          
class TestFixtureBase
{     
public:
	virtual void run() = 0;
};

template <typename T>
class TestFixture : public TestFixtureBase
{  
	typedef void (*TestMethod)();	
	map<string, TestMethod> _testMethods;
	
public:
	void run()
	{
		
	}	 
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
class fixture


TestFixture(MyTestCase)
{   
};

TestFixture(MySecondTestCase)
{
public:
   	void Test()
    {
		cout << "Running test" << endl;
    }
};
                            

int main()
{            
	cout << "Igloo" << endl; 
	
	for(TestFixtureMap::iterator it = fixtureMap.begin(); it != fixtureMap.end(); it++)
	{
		cout << "Running test: " << (*it).first << endl;
		(*it).second->run();
	}
	
	return 0;
}