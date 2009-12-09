
#include "igloo.hpp"
#include "constraints/is.h"

TestFixture(Assertions)
{
  public:

  TestMethod(Assertions, ShouldHandleIntegerEquality)
  {
    Assert::That(5, Is<int>().EqualTo(5));
  }

  TestMethod(Assertions, ShouldDetectIntegerInequality)
  {
    bool exceptionIsThrown = false;

    try
    {
      Assert::That(5, Is<int>().EqualTo(4));
    }
    catch (AssertionException)
    {
      exceptionIsThrown = true;
    }

    Assert::That(exceptionIsThrown);
  }

  TestMethod(Assertions, ShouldHandleNotOperators)
  {
    Assert::That(5, Is<int>().Not().EqualTo(4));
  }

  TestMethod(Assertions, ShouldDetectIfNotFails)
  {
    bool exceptionIsThrown = false;

    try
    {
      Assert::That(5, Is<int>().Not().EqualTo(5));
    }
    catch (AssertionException)
    {
      exceptionIsThrown = true;
    }

    Assert::That(exceptionIsThrown);
  }

  TestMethod(Assertions, ShouldHandleStrings)
  {
    Assert::That<string>("joakim", Is<string>().EqualTo("joakim"));
  }
};

int main()
{
  return TestRunner::RunAllTests();
}
