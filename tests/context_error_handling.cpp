
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

Context(AContextWithAFailingSpec)
{
  
  void SetUp()
  {
    failing_context.SetName("FailingContext");
  }

  Spec(FailingSpecShouldBeRegisteredAsFailed)
  {
    ContextRegistry<FailingContext>::CallSpec(failing_context, "AFailingSpec", &FailingContext::AFailingSpec, results);
    
    Assert::That(results.FailedTests(), HasLength(1));
    Assert::That(results.FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("FailingContext", "AFailingSpec", "This should fail")));    
  }
  
  struct FailingContext : public ContextProvider<FailingContext, ContextBase>
  {
    Spec(AFailingSpec)
    {
      Assert::Failure("This should fail");
    }
  } failing_context;
  
  TestResults results;
};


Context(AContextWithAFailingTearDown)
{
  
  void SetUp()
  {
    failing_context.SetName("FailingContext");
  }

  Spec(SpecShouldBeRegisteredAsFailed)
  {
    ContextRegistry<FailingContext>::CallSpec(failing_context, "TrivialSpec", &FailingContext::TrivialSpec, results);
    
    Assert::That(results.FailedTests(), HasLength(1));
    Assert::That(results.FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("FailingContext", "TrivialSpec", "This should fail")));    
  }
  
  struct FailingContext : public ContextProvider<FailingContext, ContextBase>
  {
    void TearDown()
    {
      Assert::Failure("This should fail");
    }
    
    Spec(TrivialSpec)
    {
    }
    
  } failing_context;
  
  TestResults results;
};
