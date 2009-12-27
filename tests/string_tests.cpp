#include "../igloo.hpp"
using igloo::Assert;

TestFixture(StringConstraints)
{
  TestMethod(StringConstraints, ShouldHandleOfLength)
  {
    Assert::That("12345", Is().String().OfLength(5));
  }
};
