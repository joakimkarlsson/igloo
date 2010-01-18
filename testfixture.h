#ifndef IGLOO_TESTFIXTURE_H
#define IGLOO_TESTFIXTURE_H

#include "assertionexception.h"
#include "assert.h"
#include "testresult.h"
#include "syntax.h"

namespace igloo {

  class TestFixtureBase
  {
  public:
    virtual void Run(const std::string& fixtureName, std::list<TestResult>& results) = 0;

  protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    RootNode Is()
    {
      RootNode node;
      return node;
    }
  };

  template <typename FixtureType>
  class TestFixture : public TestFixtureBase
  {
  public:
    typedef FixtureType IGLOO_FIXTURE_TYPE;

    static void RegisterTestMethod(const std::string& name, void (IGLOO_FIXTURE_TYPE::*method)())
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

#endif // IGLOO_TESTFIXTURE_H
