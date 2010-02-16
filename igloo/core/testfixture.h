
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTFIXTURE_H
#define IGLOO_TESTFIXTURE_H

#include <igloo/core/assertionexception.h>
#include <igloo/core/assert.h>
#include <igloo/core/testresult.h>

namespace igloo {

  struct TestFixtureBase
  {
    virtual ~TestFixtureBase() {}
    
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
       
    ExpressionBuilder<Nil> Is()
    {
      return ExpressionBuilder<Nil>(Nil());
    }

    ExpressionBuilder<Nil> Has()
    {
       return ExpressionBuilder<Nil>(Nil());
    }
  };
  
  template <typename FixtureType>
  struct BaseFixture : public TestFixtureBase 
  {
    typedef FixtureType IGLOO_FIXTURE_TYPE;

    static void RegisterTestMethod(const std::string& name, void (FixtureType::*method)())
    {
      GetTestMethods().insert(std::make_pair(name, method));
    }

    static void Run(FixtureType& testFixture, const std::string& fixtureName, std::list<TestResult>& results)
    {    
      const TestMethods& testMethods = GetTestMethods();
      CallTests(testFixture, testMethods, fixtureName, results);
    }

  private:
    typedef void (FixtureType::*TestMethodPtr)();
    typedef std::map<std::string, TestMethodPtr> TestMethods;
    
    static void CallTests(FixtureType& fixture, const TestMethods& testMethods, const std::string& fixtureName, std::list<TestResult>& results)
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
    
    static bool CallTest(FixtureType& fixture, const std::string& fixtureName, const std::string& testName, TestMethodPtr method, std::list<TestResult>& results)
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
        fixture.TearDown();
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
