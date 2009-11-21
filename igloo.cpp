#include <map>    

using namespace std;
 

class TestFixtureFactory
{
};  
                                          
class TestFixtureBase
{
};

template <typename T>
class TestFixture : public TestFixtureBase
{ 
};

typedef map<string, TestFixtureBase* > TestFixtureMap;
TestFixtureMap fixtureMap;

int RegisterTest(string name, TestFixtureBase* testFixture)
{        
	fixtureMap[name] = testFixture; 
	return 0;
}  

#define TestFixture(fixture) \
class fixture; \
int fixture##_dummy = RegisterTest( #fixture , new TestFixture<fixture>()); \
class fixture


TestFixture(MyTestCase)
{   
};

TestFixture(MySecondTestCase)
{
public:
		
};
        
// class MyTestCase; 
// int x = RegisterTest("MyTestCase", new TestFixture<MyTestCase>() ) ;
// class MyTestCase
// {                                              	
// }; 
                       

int main()
{            
	cout << "Igloo" << endl; 
	
	for(TestFixtureMap::iterator it = fixtureMap.begin(); it != fixtureMap.end(); it++)
	{
		cout << "Found test " << (*it).first << endl;
	}
	
	return 0;
}