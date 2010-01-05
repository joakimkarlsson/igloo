#include "../igloo.hpp"

using igloo::Assert;
using igloo::AssertionException;
using igloo::TestRunner;

int dummy;

TestFixture(Assertions)
{
  public:

  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }

  TestMethod(Assertions, ShouldHandleIntegerEquality)
  {
    Assert::That(5, Is().EqualTo(5));
  }

  TestMethod(Assertions, ShouldDetectIntegerInequality)
  {
    bool exceptionIsThrown = false;

    try
    {
      Assert::That(5, Is().EqualTo(4));
    }
    catch (const AssertionException&)
    {
      exceptionIsThrown = true;
    }

    Assert::That(exceptionIsThrown);
  }

  TestMethod(Assertions, ShouldHandleNotOperators)
  {
    Assert::That(5, Is().Not().EqualTo(4));
  }

  TestMethod(Assertions, ShouldDetectIfNotFails)
  {
    bool exceptionIsThrown = false;

    try
    {
      Assert::That(5, Is().Not().EqualTo(5));
    }
    catch (const AssertionException&)
    {
      exceptionIsThrown = true;
    }

    Assert::That(exceptionIsThrown);
  }

  TestMethod(Assertions, ShouldHandleStrings)
  {
    Assert::That("joakim", Is().EqualTo("joakim"));
  }

  TestMethod(Assertions, ShouldHandleNotOperatorsForStrings)
  {
    Assert::That("joakim", Is().Not().EqualTo("harry"));
  }

  TestMethod(Assertions, ShouldHandleStringsWithoutExplicitTemplateQualification)
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
    std::string errorText;

    try
    {
      Assert::That(5, Is().GreaterThan(5));
    }
    catch (const AssertionException exception)
    {
      errorText = exception.GetMessage();
    }

    Assert::That(errorText, Is().EqualTo("Expected: greater than 5\nActual: 5\n"));
  }

  TestMethod(Assertions, ShouldHandleLessThan)
  {
    Assert::That(5, Is().LessThan(6));
  }

  TestMethod(Assertions, ShouldDetectWhenLessThanFails)
  {
    std::string errorText;

    try
    {
      Assert::That(6, Is().LessThan(5));
    }
    catch (const AssertionException exception)
    {
      errorText = exception.GetMessage();
    }

    Assert::That(errorText, Is().EqualTo("Expected: less than 5\nActual: 6\n"));
  }

  TestMethod(Assertions, ShouldHandleCompoundOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().LessThan(6));
  }

  TestMethod(Assertions, ShouldHandleBothLeftAndRightAssociativeOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().Not().LessThan(3));
  }

  TestMethod(Assertions, ShouldHandleStringContainsConstraint)
  {
    Assert::That("abcdef", Is().Containing("bcde"));
  }

  TestMethod(Assertions, StringConstraintShouldHandleMatchAtBeginningOfString)
  {
    Assert::That("abcdef", Is().Containing("a"));
  }

  TestMethod(Assertions, ShouldHandleStringStartingWithConstraint)
  {
    Assert::That("abcdef", Is().StartingWith("abc"));
  }

  TestMethod(Assertions, ShouldHandleStringEndingWithConstraint)
  {
    Assert::That("abcdef", Is().EndingWith("def"));
  }

  TestMethod(Assertions, ShouldHandleOperatorsWithStringConstraints)
  {
    Assert::That("abcdef", Is().StartingWith("ab").And().EndingWith("ef"));
  }

  TestMethod(Assertions, ShouldHandleStringConstraintsWithMultipleOperators)
  {
    Assert::That("abcdef", Is().StartingWith("ab").And().Not().EndingWith("qwqw"));
  }

  TestMethod(Assertions, ShouldThrowExplicitFailureMessage)
  {
    std::string assertionMessage;
    
    try
    {
      Assert::Failure("foo");
    }
    catch (const AssertionException& e)
    {
      assertionMessage = e.GetMessage();
    }

    Assert::That(assertionMessage, Is().EqualTo("Forced failure: foo"));
  }
};

int main()
{
  return TestRunner::RunAllTests();
}
