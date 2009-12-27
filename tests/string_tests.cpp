#include "../igloo.hpp"
using igloo::Assert;

TestFixture(StringConstraints)
{
  TestMethod(StringConstraints, ShouldHandleOfLength)
  {
    Assert::That("12345", Is().String().OfLength(5));
  }

  TestMethod(StringConstraints, ShouldHandleWeirdLongExpressions)
  {
    Assert::That("12345", Is().String().OfLength(5).And().StartingWith("123").And().Not().EndingWith("zyxxy"));
  }
};
