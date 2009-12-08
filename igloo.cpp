
#include "igloo.hpp"

TestFixture(AssertionTests)
{
  public:

  TestMethod(AssertionTests, TestEquality)
  {
    bool exceptionIsThrown = false;
    try
    {
      Assert::That(5, Is.EqualTo(4));
    }
    catch (AssertionException)
    {
      exceptionIsThrown = true;
    }

    Assert::That(exceptionIsThrown);
  }

  TestMethod(AssertionTests, Test2)
  {
    Assert::That("Joakim", Is.EqualTo("Harry"));
  }

  TestMethod(AssertionTests, NotOperator)
  {
    Assert::That("Joakim", Is.Not.EqualTo("Joakim"));
  }
};

int main()
{
  return TestRunner::RunAllTests();
}
