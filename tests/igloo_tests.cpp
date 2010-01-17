#include "igloo_self_test.h"

using namespace igloo;

TestFixture(Assertions)
{
  TestMethod(ShouldHandleIntegerEquality)
  {
    Assert::That(5, Equals(5));
  }

  TestMethod(ShouldDetectIntegerInequality)
  {
    AssertTestFails(Assert::That(5, Equals(4)), "equal to 4");
  }

  TestMethod(ShouldDetectIfNotFails)
  {
    AssertTestFails(Assert::That(5, !Equals(5)), "Expected: not equal to 5\nActual: 5\n");
  }

  TestMethod(ShouldHandleStrings)
  {
    Assert::That(std::string("joakim"), Equals(std::string("joakim")));
  }

  TestMethod(ShouldHandleStringsWithoutExplicitTemplateSpecialization)
  {
    Assert::That("kim", Equals("kim"));
  }

  TestMethod(ShouldHandleGreaterThan)
  {
    Assert::That(5, IsGreaterThan(4));
  }

  TestMethod(ShouldDetectWhenGreaterThanFails)
  {
    AssertTestFails(Assert::That(5, IsGreaterThan(5)), "Expected: greater than 5\nActual: 5\n");
  }

  TestMethod(ShouldHandleLessThan)
  {
    Assert::That(5, IsLessThan(6));
  }

  TestMethod(ShouldDetectWhenLessThanFails)
  {
    AssertTestFails(Assert::That(6, IsLessThan(5)), "Expected: less than 5\nActual: 6\n");
  }

  TestMethod(ShouldThrowExplicitFailureMessage)
  {
    AssertTestFails(Assert::Failure("foo"), "Forced failure: foo");
  }
};

TestFixture(WeCanHaveSeveralFixturesInTheSameFile)
{
};
