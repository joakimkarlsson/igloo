#include "igloo_self_test.h"

using igloo::Assert;
using igloo::AssertionException;

TestFixture(Assertions)
{
  TestMethod(Assertions, ShouldHandleIntegerEquality)
  {
    Assert::That(5, Is().EqualTo(5));
  }

  TestMethod(Assertions, ShouldDetectIntegerInequality)
  {
    AssertTestFails(Assert::That(5, Is().EqualTo(4)), "equal to 4");
  }

  TestMethod(Assertions, ShouldHandleNotOperators)
  {
    Assert::That(5, Is().Not().EqualTo(4));
  }

  TestMethod(Assertions, ShouldDetectIfNotFails)
  {
    AssertTestFails( Assert::That(5, Is().Not().EqualTo(5)), "not equal to 5");
  }

  TestMethod(Assertions, ShouldHandleStrings)
  {
    Assert::That(std::string("joakim"), Is().EqualTo(std::string("joakim")));
  }

  TestMethod(Assertions, ShouldHandleNotOperatorsForStrings)
  {
    Assert::That("joakim", Is().Not().EqualTo("harry"));
  }

  TestMethod(Assertions, ShouldHandleStringsWithoutExplicitTemplateSpecialization)
  {
    Assert::That("kim", Is().EqualTo("kim"));
  }

  TestMethod(Assertions, ShouldReturnAReadableErrorTextUponFailure)
  {
    std::string errorText;

    try
    {
      Assert::That(5, Is().Not().EqualTo(5));
    }
    catch (const AssertionException& exception)
    {
      errorText = exception.GetMessage();
    }

    Assert::That(errorText, Is().EqualTo("Expected: not equal to 5\nActual: 5\n"));
  }

  TestMethod(Assertions, ShouldHandleGreaterThan)
  {
    Assert::That(5, Is().GreaterThan(4));
  }

  TestMethod(Assertions, ShouldDetectWhenGreaterThanFails)
  {
    AssertTestFails(Assert::That(5, Is().GreaterThan(5)), "Expected: greater than 5\nActual: 5\n");
  }

  TestMethod(Assertions, ShouldHandleLessThan)
  {
    Assert::That(5, Is().LessThan(6));
  }

  TestMethod(Assertions, ShouldDetectWhenLessThanFails)
  {
    AssertTestFails(Assert::That(6, Is().LessThan(5)), "Expected: less than 5\nActual: 6\n");
  }

  TestMethod(Assertions, ShouldHandleCompoundOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().LessThan(6));
  }

  TestMethod(Assertions, ShouldHandleBothLeftAndRightAssociativeOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().Not().LessThan(3));
  }

  TestMethod(Assertions, ShouldThrowExplicitFailureMessage)
  {
    AssertTestFails(Assert::Failure("foo"), "Forced failure: foo");
  }
};
