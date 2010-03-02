
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

  struct ContextBase 
  {
    virtual ~ContextBase() {}
    
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
  
  template <typename ContextToCall>
  struct ContextRegistry  
  {
    static void RegisterSpec(const std::string& name, void (ContextToCall::*spec)())
    {
      GetSpecs().insert(std::make_pair(name, spec));
    }

    template <typename ContextToCreate>
    static void Run(const std::string& contextName, std::list<TestResult>& results)
    {    
      const TestMethods& testMethods = GetSpecs();
      CallTests<ContextToCreate>(testMethods, contextName, results);
    }

    typedef void (ContextToCall::*TestMethodPtr)();
    typedef std::map<std::string, TestMethodPtr> TestMethods;
    
    template <typename ContextToCreate>
    static void CallTests(const TestMethods& testMethods, const std::string& contextName, std::list<TestResult>& results)
    {
      ContextToCreate c;

      typename TestMethods::const_iterator it;
      for (it = testMethods.begin(); it != testMethods.end(); it++)
      {
        ContextToCreate context;
        if(CallTest(context, contextName, (*it).first, (*it).second, results))
        {
          std::cout << ".";
        }
        else
        {
          std::cout << "F";
        }
      }
    }

    static bool CallTest(ContextToCall& context, const std::string& contextName, const std::string& specName, TestMethodPtr method, std::list<TestResult>& results)
    {
      bool result = true;
      
      try
      {
        context.IglooFrameworkSetUp();
        (context.*method)();
       }
      catch (const AssertionException& e)
      {
        results.push_back(TestResult(contextName, specName, false, e.GetMessage()));
        result == false;
      }
      
      try 
      {
        context.IglooFrameworkTearDown();
      }
      catch (const AssertionException&) 
      {
      }
      
      if(result)
      {
        results.push_back(TestResult(contextName, specName, true, "Test succeeded"));
      }
      
      return result;
    }

    static TestMethods& GetSpecs()
    {
      static TestMethods testMethods;
      return testMethods;
    }
  };  
}

#endif // IGLOO_TESTFIXTURE_H
