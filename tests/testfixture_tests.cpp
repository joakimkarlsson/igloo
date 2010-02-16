
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "igloo_self_test.h"
using namespace igloo;

namespace {
  struct FakeFixture : public BaseFixture<FakeFixture>
  {
    FakeFixture() : tearDownIsCalled(0)
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
    
    int tearDownIsCalled;    
  };
}

TestFixture(TestFixtureTests)
{
  TestMethod(TearDownIsCalledWhenTestMethodFails)
  {
    FakeFixture t;
    RunFixture(t);
    
    Assert::That(t.tearDownIsCalled, Equals(1));
  }
  
  template< typename FixtureType >
  void RunFixture(FixtureType& fixture)
  {
    std::list<TestResult> results;
    FixtureType::Run(fixture, "Irrelevant", results);
  }
};
