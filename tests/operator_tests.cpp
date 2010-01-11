#include "igloo_self_test.h"

using namespace igloo;

TestFixture(OperatorTests)
{
  TestMethod(OperatorTests, ShouldHandleAndOperator)
  {
    Assert::That(5, Is().LessThan(6).And().GreaterThan(4));
  }

  TestMethod(OperatorTests, ShouldHandleAndOperatorFail)
  {
    AssertTestFails(Assert::That(5, Is().LessThan(7).And().GreaterThan(5)), "less than 7 and greater than 5");
  }

  TestMethod(OperatorTests, ShouldHandleOrOperator)
  {
    Assert::That(12, Is().LessThan(7).Or().GreaterThan(5));
  }
};
