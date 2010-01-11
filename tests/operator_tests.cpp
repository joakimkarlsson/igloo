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

  TestMethod(OperatorTests, ShouldHandleOrOperatorFails)
  {
    AssertTestFails(Assert::That(67, Is().LessThan(12).Or().GreaterThan(99)), "less than 12 or greater than 99");
  }

  TestMethod(OperatorTests, ShouldHandleNotOperators)
  {
    Assert::That(5, Is().Not().EqualTo(4));
  }

  TestMethod(OperatorTests, ShouldHandleNotOperatorsFails)
  {
    AssertTestFails(Assert::That(12, Is().Not().EqualTo(12)), "not equal to 12");
  }

  TestMethod(OperatorTests, ShouldHandleNotOperatorsForStrings)
  {
    Assert::That("joakim", Is().Not().EqualTo("harry"));
  }

  TestMethod(OperatorTests, ShouldHandleBothLeftAndRightAssociativeOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().Not().LessThan(3));
  }
};
