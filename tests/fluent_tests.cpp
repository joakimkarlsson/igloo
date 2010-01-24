#include "igloo_self_test.h"

using namespace igloo;

TestFixture(FluentTests)
{
  TestMethod(SimpleEqualsContraints)
  {
    Assert::That(5, Iz().EqualTo(5));
  }
};

