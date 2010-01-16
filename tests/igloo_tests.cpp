#include "igloo_self_test.h"

using igloo::Assert;
using igloo::AssertionException;

TestFixture(Assertions)
{
  TestMethod(ShouldHandleIntegerEquality)
  {
    Assert::That(5, Is().EqualTo(5));
  }

  TestMethod(ShouldDetectIntegerInequality)
  {
    AssertTestFails(Assert::That(5, Is().EqualTo(4)), "equal to 4");
  }

  TestMethod(ShouldDetectIfNotFails)
  {
    AssertTestFails( Assert::That(5, Is().Not().EqualTo(5)), "Expected: not equal to 5\nActual: 5\n");
  }

  TestMethod(ShouldHandleStrings)
  {
    Assert::That(std::string("joakim"), Is().EqualTo(std::string("joakim")));
  }

  TestMethod(ShouldHandleStringsWithoutExplicitTemplateSpecialization)
  {
    Assert::That("kim", Is().EqualTo("kim"));
  }

  TestMethod(ShouldHandleGreaterThan)
  {
    Assert::That(5, Is().GreaterThan(4));
  }

  TestMethod(ShouldDetectWhenGreaterThanFails)
  {
    AssertTestFails(Assert::That(5, Is().GreaterThan(5)), "Expected: greater than 5\nActual: 5\n");
  }

  TestMethod(ShouldHandleLessThan)
  {
    Assert::That(5, Is().LessThan(6));
  }

  TestMethod(ShouldDetectWhenLessThanFails)
  {
    AssertTestFails(Assert::That(6, Is().LessThan(5)), "Expected: less than 5\nActual: 6\n");
  }

  TestMethod(ShouldThrowExplicitFailureMessage)
  {
    AssertTestFails(Assert::Failure("foo"), "Forced failure: foo");
  }
};

TestFixture(WeCanHaveSeveralFixturesInTheSameFile)
{
};
