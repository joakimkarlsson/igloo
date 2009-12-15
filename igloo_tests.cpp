
#include "igloo.hpp"

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
    catch (AssertionException)
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
    catch (AssertionException)
    {
      exceptionIsThrown = true;
    }

    Assert::That(exceptionIsThrown);
  }

  TestMethod(Assertions, ShouldHandleStrings)
  {
    Assert::That<string > ("joakim", Is().EqualTo<string > ("joakim"));
  }

  TestMethod(Assertions, ShouldHandleNotOperatorsForStrings)
  {
    Assert::That<string > ("joakim", Is().Not().EqualTo<string > ("harry"));
  }

  TestMethod(Assertions, ShouldReturnAReadableErrorTextUponFailure)
  {
    string errorText;

    try
    {
      Assert::That(5, Is().Not().EqualTo(5));
    }
    catch(AssertionException exception)
    {
      errorText = exception.GetMessage();
    }

    Assert::That<string>(errorText, Is().EqualTo<string>("Expected: not equal to 5\nActual: 5\n"));
  }
};

int main()
{
  return TestRunner::RunAllTests();
}
