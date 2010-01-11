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

  TestMethod(OperatorTests, ShouldHandleNotOperators)
  {
    Assert::That(5, Is().Not().EqualTo(4));
  }

  TestMethod(OperatorTests, ShouldHandleNotOperatorsForStrings)
  {
    Assert::That("joakim", Is().Not().EqualTo("harry"));
  }

  TestMethod(OperatorTests, ShouldHandleCompoundOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().LessThan(6));
  }

  TestMethod(OperatorTests, ShouldHandleBothLeftAndRightAssociativeOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().Not().LessThan(3));
  }
};
