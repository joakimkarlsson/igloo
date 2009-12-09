
#include "igloo.hpp"
#include "constraints/is.h"

TestFixture(AssertionTests)
{
  public:

  TestMethod(AssertionTests, Experimental)
  {
    Assert::That(5, Is().Not().Not().EqualTo(5));
  }
};

int main()
{
  return TestRunner::RunAllTests();
}
