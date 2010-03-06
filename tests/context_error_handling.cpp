
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

Context(AContextWithAFailingSpec)
{
  
  Spec(FailingSpecShouldBeRegisteredAsFailed)
  {
    ContextRegistry<FailingContext>::CallSpec(failing_context, "FailingContext", "AFailingSpec", &FailingContext::AFailingSpec, results);
    
    Assert::That(results, HasLength(1));
    Assert::That(results, Has().Exactly(1).EqualTo(TestResult("FailingContext", "AFailingSpec", false, "This should fail")));    
  }
  
  struct FailingContext : public ContextProvider<FailingContext, ContextBase>
  {
    Spec(AFailingSpec)
    {
      Assert::Failure("This should fail");
    }
  } failing_context;
  
  std::list<TestResult> results;
};


Context(AContextWithAFailingTearDown)
{
  
  Spec(SpecShouldBeRegisteredAsFailed)
  {
    ContextRegistry<FailingContext>::CallSpec(failing_context, "FailingContext", "TrivialSpec", &FailingContext::TrivialSpec, results);
    
    Assert::That(results, HasLength(1));
    Assert::That(results, Has().Exactly(1).EqualTo(TestResult("FailingContext", "TrivialSpec", false, "This should fail")));    
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
  
  std::list<TestResult> results;
};
