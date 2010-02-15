#include "igloo_self_test.h"
using namespace igloo;

namespace {
  struct FakeFixture : public BaseFixture<FakeFixture>
  {
    FakeFixture() : tearDownIsCalled(0)
    {
    }
        
    void SetUp()
    {}
    
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
    std::list<TestResult> results;
    FakeFixture::Run(t, "Irrelevant", results);
    
    Assert::That(t.tearDownIsCalled, Equals(1));
  }
};
