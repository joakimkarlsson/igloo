#include "../igloo.h"

using namespace igloo;

TestFixture(OperatorTests)
{
  TestMethod(OperatorTests, ShouldHandleAndOperator)
  {
    Assert::That(5, Is().LessThan(6).And().GreaterThan(4));
  }

  TestMethod(OperatorTests, ShouldHandleAndOperatorFail)
  {
    bool exception_thrown = false;

    try
    {
      Assert::That(5, Is().LessThan(7).And().GreaterThan(5));
    }
    catch(const AssertionException& e)
    {
      exception_thrown = true;
    }

    Assert::That(exception_thrown);
  }

  TestMethod(OperatorTests, ShouldHandleOrOperator)
  {
    Assert::That(12, Is().LessThan(7).Or().GreaterThan(5));
  }
};
