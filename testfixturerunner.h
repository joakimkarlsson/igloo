#ifndef IGLOO_TESTFIXTURERUNNER_H
#define IGLOO_TESTFIXTURERUNNER_H

namespace igloo {
 
  struct TestFixtureRunnerBase
  {
    virtual void Run(const std::string& fixtureName, std::list<TestResult>& results) = 0;    
  };
  
  template <typename FixtureType>
  class TestFixtureRunner : public TestFixtureRunnerBase
  {
  public:
    static void RegisterTestMethod(const std::string& name, void (FixtureType::*method)())
    {
      GetTestMethods().insert(std::make_pair(name, method));
    }
    
    void Run(const std::string& fixtureName, std::list<TestResult>& results)
    {
      FixtureType testFixture;
      
      const TestMethods& testMethods = GetTestMethods();
      CallTests(testFixture, testMethods, fixtureName, results);
    }
    
  private:
    typedef void (FixtureType::*TestMethodPtr)();
    typedef std::map<std::string, TestMethodPtr> TestMethods;
    
    void CallTests(FixtureType& fixture, const TestMethods& testMethods, const std::string& fixtureName, std::list<TestResult>& results)
    {
      typename TestMethods::const_iterator it;
      for (it = testMethods.begin(); it != testMethods.end(); it++)
      {
        if(CallTest(fixture, fixtureName, (*it).first, (*it).second, results))
        {
          std::cout << ".";
        }
        else
        {
          std::cout << "F";
        }
      }
    }
    
    bool CallTest(FixtureType& fixture, const std::string& fixtureName, const std::string& testName, TestMethodPtr method, std::list<TestResult>& results)
    {
      try
      {
        fixture.SetUp();
        (fixture.*method)();
        fixture.TearDown();
      }
      catch (const AssertionException& e)
      {
        results.push_back(TestResult(fixtureName, testName, false, e.GetMessage()));
        return false;
      }
      
      results.push_back(TestResult(fixtureName, testName, true, "Test succeeded"));
      return true;
    }
    
    static TestMethods& GetTestMethods()
    {
      static TestMethods testMethods;
      return testMethods;
    }
  };
  
  
}

#endif
