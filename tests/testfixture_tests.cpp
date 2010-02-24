
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "igloo_self_test.h"
using namespace igloo;

namespace {
  struct FakeFixture : public BaseFixture<FakeFixture>
  {
    FakeFixture()
    {
    }
        
    void TearDown()
    {
      tearDownIsCalled++;
    }
    
    TestMethod(MethodThatFails)
    {
      Assert::Failure("This fails!");
    }
    
    static int tearDownIsCalled;
  };
}

int FakeFixture::tearDownIsCalled = 0;

TestFixture(TestFixtureTests)
{
  TestMethod(TearDownIsCalledWhenTestMethodFails)
  {
    FakeFixture::tearDownIsCalled = 0;
    RunFixture<FakeFixture>();
    Assert::That(FakeFixture::tearDownIsCalled, Equals(1));
  }
  
  template< typename FixtureType >
  void RunFixture()
  {
    std::list<TestResult> results;
    FixtureType::template Run<FixtureType>("Irrelevant", results);
  }
};

TestFixture(AFreshTestFixtureIsCreatedForEachMethod)
{
  AFreshTestFixtureIsCreatedForEachMethod() : member("unaltered")
  {
  }

  TestMethod(ThisMethodShouldHaveItsOwnContext)
  {
    Assert::That(member, Equals("unaltered"));
    member = "altered";
  }

  TestMethod(ThisMethodShouldAlsoHaveItsOwnContext)
  {
    Assert::That(member, Equals("unaltered"));
    member = "altered";
  }

  std::string member;
};
