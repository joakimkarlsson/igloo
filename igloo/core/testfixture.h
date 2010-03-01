
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
    
    virtual void IglooFrameworkSetUp()
    {}
    
    virtual void IglooFrameworkTearDown()
    {}
    
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
  
  template <typename FixtureToCall>
  struct BaseFixture : public TestFixtureBase 
  {
    typedef FixtureToCall IGLOO_FIXTURE_TYPE;

    static void RegisterTestMethod(const std::string& name, void (FixtureToCall::*method)())
    {
      GetTestMethods().insert(std::make_pair(name, method));
    }

    template <typename FixtureToInstantiate>
    static void Run(const std::string& fixtureName, std::list<TestResult>& results)
    {    
      const TestMethods& testMethods = GetTestMethods();
      CallTests<FixtureToInstantiate>(testMethods, fixtureName, results);
    }

    typedef void (FixtureToCall::*TestMethodPtr)();
    typedef std::map<std::string, TestMethodPtr> TestMethods;
    
    template <typename FixtureToInstantiate>
    static void CallTests(const TestMethods& testMethods, const std::string& fixtureName, std::list<TestResult>& results)
    {
      FixtureToInstantiate f;

      typename TestMethods::const_iterator it;
      for (it = testMethods.begin(); it != testMethods.end(); it++)
      {
        FixtureToInstantiate newFixture;
        if(CallTest(newFixture, fixtureName, (*it).first, (*it).second, results))
        {
          std::cout << ".";
        }
        else
        {
          std::cout << "F";
        }
      }
    }

    static bool CallTest(FixtureToCall& fixture, const std::string& fixtureName, const std::string& testName, TestMethodPtr method, std::list<TestResult>& results)
    {
      bool result = true;
      
      try
      {
        fixture.IglooFrameworkSetUp();
        (fixture.*method)();
       }
      catch (const AssertionException& e)
      {
        results.push_back(TestResult(fixtureName, testName, false, e.GetMessage()));
        result == false;
      }
      
      try 
      {
        fixture.IglooFrameworkTearDown();
      }
      catch (const AssertionException&) 
      {
      }
      
      if(result)
      {
        results.push_back(TestResult(fixtureName, testName, true, "Test succeeded"));
      }
      
      return result;
    }

    static TestMethods& GetTestMethods()
    {
      static TestMethods testMethods;
      return testMethods;
    }
  };  
}

#endif // IGLOO_TESTFIXTURE_H
