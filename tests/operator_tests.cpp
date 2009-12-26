#include "../igloo.hpp"
using igloo::Assert;

TestFixture(OperatorTests)
{

  TestMethod(OperatorTests, ShouldHandleAndOperator)
  {
    Assert::That(5, Is().LessThan(6).And().GreaterThan(4));
  }
};
