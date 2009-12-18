
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
    catch(const AssertionException& exception)
    {
      errorText = exception.GetMessage();
    }

    Assert::That(errorText, Is().EqualTo("Expected: not equal to 5\nActual: 5\n"));
  }
};

int main()
{
  return TestRunner::RunAllTests();
}
