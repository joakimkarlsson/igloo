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
