#include <map>    
#include <vector>
using namespace std;
                                           
class TestFixtureBase
{     
public:
	virtual void Run() = 0;
	virtual void RegisterTestMethods() {}      
};

template <typename T>
class TestFixture : public TestFixtureBase
{
public:     	
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
   
	void GetTests(vector<void (T::*)() >& testMethods)
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

	virtual void GetTest0(vector<void (T::*)() >&) { cout << "Base::GetTest0" << endl;} 
   virtual void GetTest1(vector<void (T::*)() >&) {} 
   virtual void GetTest2(vector<void (T::*)() >&) {} 
   virtual void GetTest3(vector<void (T::*)() >&) {} 
   virtual void GetTest4(vector<void (T::*)() >&) {} 
   virtual void GetTest5(vector<void (T::*)() >&) {} 
   virtual void GetTest6(vector<void (T::*)() >&) {} 
   virtual void GetTest7(vector<void (T::*)() >&) {} 
   virtual void GetTest8(vector<void (T::*)() >&) {} 
   virtual void GetTest9(vector<void (T::*)() >&) {} 
   virtual void GetTest10(vector<void (T::*)() >&) {} 
   virtual void GetTest11(vector<void (T::*)() >&) {} 
   virtual void GetTest12(vector<void (T::*)() >&) {} 
   virtual void GetTest13(vector<void (T::*)() >&) {} 
   virtual void GetTest14(vector<void (T::*)() >&) {} 
   virtual void GetTest15(vector<void (T::*)() >&) {} 
   virtual void GetTest16(vector<void (T::*)() >&) {} 
   virtual void GetTest17(vector<void (T::*)() >&) {} 
   virtual void GetTest18(vector<void (T::*)() >&) {} 
   virtual void GetTest19(vector<void (T::*)() >&) {} 
   virtual void GetTest20(vector<void (T::*)() >&) {} 
};

typedef map<string, TestFixtureBase* > TestFixtureMap;
TestFixtureMap fixtureMap;

int RegisterTestFixture(string name, TestFixtureBase* testFixture)
{        
	fixtureMap[name] = testFixture; 
	testFixture->RegisterTestMethods();
	return 0;
}  
         
TestFixture(MyTestCase)
{      			
public:      
   
	void GetTest0(vector< void (*)() >& tests)  
	{       
		cout << "MyTestCase::GetTest0" << endl;
		tests.push_back(&MyTestCase::Test1);
	}   	
    void Test1()
    {
		cout << "  Running Test1" << endl;   	
    }
    
	void GetTest1(vector< void (MyTestCase::*)() >& tests)  
	{
		tests.push_back(&MyTestCase::Test2);
	}
 	void Test2()
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