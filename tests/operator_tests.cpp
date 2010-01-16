#include "igloo_self_test.h"

#include "../constraints/equalsconstraint.h"
#include "../constraints/islessthanconstraint.h"
#include "../constraints/isgreaterthanconstraint.h"

using namespace igloo;

TestFixture(OperatorTests)
{
  TestMethod(ShouldHandleAndOperator)
  {
    Assert::That(5, IsLessThan(6) && IsGreaterThan(4));
  }

  TestMethod(ShouldHandleAndOperatorFail)
  {
    AssertTestFails(Assert::That(5, IsLessThan(7) && IsGreaterThan(5)), "less than 7 and greater than 5");
  }

  TestMethod(ShouldHandleOrOperator)
  {
    Assert::That(12, IsLessThan(7) || IsGreaterThan(5));
  }

  TestMethod(ShouldHandleOrOperatorFails)
  {
    AssertTestFails(Assert::That(67, IsLessThan(12) || IsGreaterThan(99)), "less than 12 or greater than 99");
  }

  TestMethod(ShouldHandleNotOperators)
  {
    Assert::That(5, !Equals(4));
  }

  TestMethod(ShouldHandleNotOperatorsFails)
  {
    AssertTestFails(Assert::That(12, !Equals(12)), "not equal to 12");
  }

  TestMethod(ShouldHandleNotOperatorsForStrings)
  {
    Assert::That("joakim", !Equals("harry"));
  }

  TestMethod(ShouldHandleBothLeftAndRightAssociativeOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().Not().LessThan(3));
    Assert::That(5, IsGreaterThan(4)&& !IsLessThan(3));
  }
};
