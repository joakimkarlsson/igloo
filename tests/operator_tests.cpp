#include "igloo_self_test.h"

using namespace igloo;

TestFixture(OperatorTests)
{
  TestMethod(ShouldHandleAndOperator)
  {
    Assert::That(5, Is().LessThan(6).And().GreaterThan(4));
  }

  TestMethod(ShouldHandleAndOperatorFail)
  {
    AssertTestFails(Assert::That(5, Is().LessThan(7).And().GreaterThan(5)), "less than 7 and greater than 5");
  }

  TestMethod(ShouldHandleOrOperator)
  {
    Assert::That(12, Is().LessThan(7).Or().GreaterThan(5));
  }

  TestMethod(ShouldHandleOrOperatorFails)
  {
    AssertTestFails(Assert::That(67, Is().LessThan(12).Or().GreaterThan(99)), "less than 12 or greater than 99");
  }

  TestMethod(ShouldHandleNotOperators)
  {
    Assert::That(5, Is().Not().EqualTo(4));
  }

  TestMethod(ShouldHandleNotOperatorsFails)
  {
    AssertTestFails(Assert::That(12, Is().Not().EqualTo(12)), "not equal to 12");
  }

  TestMethod(ShouldHandleNotOperatorsForStrings)
  {
    Assert::That("joakim", Is().Not().EqualTo("harry"));
  }

  TestMethod(ShouldHandleBothLeftAndRightAssociativeOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().Not().LessThan(3));
  }
};
