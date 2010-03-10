
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "igloo_self_test.h"
using namespace igloo;

Context(AFreshContext)
{
  AFreshContext() : member("unaltered")
  {
  }

  Spec(WhenAMethodIsCalledItShouldHaveItsOwnContext)
  {
    Assert::That(member, Equals("unaltered"));
    member = "altered";
  }

  Spec(WhenASecondMethodIsCalledItShouldAlsoHaveItsOwnContext)
  {
    Assert::That(member, Equals("unaltered"));
    member = "altered";
  }

  std::string member;
};

Context(AContextWithSetupAndTearDown)
{
  Spec(WhenASpecIsExecutedSetUpAndTearDownIsCalled)
  {
    ContextToTest contextToTest;
    ContextRegistry<ContextToTest>::CallSpec(contextToTest, "ContextToTest", "ASpec", &ContextToTest::ASpec, results);
    
    Assert::That(contextToTest.log, Equals("SetUp called TearDown called "));
  }
  
  Spec(WhenASpecInAnInnerContextIsCalledOuterSetUpAndTearDownShouldBeCalled)
  {
    ContextToTest::InnerContext innerContext;
    ContextRegistry<ContextToTest::InnerContext>::CallSpec(innerContext, "InnerContext", "ASpec", &ContextToTest::InnerContext::ASpec, results);
    
    Assert::That(innerContext.log, Equals("SetUp called Inner SetUp called Inner TearDown called TearDown called "));    
  }
  
  Spec(SetUpAndTearDownAreCalledForFailingSpecs)
  {
    ContextToTest contextToTest;
    ContextRegistry<ContextToTest>::CallSpec(contextToTest, "ContextToTest", "AFailingSpec", &ContextToTest::AFailingSpec, results);
    
    Assert::That(contextToTest.log, Equals("SetUp called TearDown called "));    
  }
  
  Spec(SetUpAndTearDownAreCalledForFailingSpecInNestedContext)
  {
    ContextToTest::InnerContext innerContext;
    ContextRegistry<ContextToTest::InnerContext>::CallSpec(innerContext, "InnerContext", "AFailingSpec", &ContextToTest::InnerContext::AFailingSpec, results);
    
    Assert::That(innerContext.log, Equals("SetUp called Inner SetUp called Inner TearDown called TearDown called "));    
  } 
  
  template<class T>
  struct ContextToTest_ : public ContextProvider<ContextToTest_<void>, ContextBase>
  {
    void SetUp()
    {
      log = "SetUp called ";
    }
    
    void TearDown()
    {
      log += "TearDown called ";
    }
    
    Spec(ASpec)
    {
    }
    
    Spec(AFailingSpec)
    {
      Assert::Failure("This should fail");
    }
    
	template<class T>
    struct InnerContext_ : public ContextProvider<InnerContext_<void>, ContextToTest_<void> >
    {
      void SetUp()
      {
        log += "Inner SetUp called ";
      }
      
      void TearDown()
      {
        log += "Inner TearDown called ";
      }
      
      Spec(ASpec)
      {
      }
      
      Spec(AFailingSpec)
      {
        Assert::Failure("This should fail");
      }      
    };

	typedef InnerContext_<void> InnerContext;

    std::string log;
  };

  typedef ContextToTest_<void> ContextToTest;
  
  std::list<TestResult> results;
};
