#include "igloo_self_test.h"

using igloo::Assert;

TestFixture(Strings)
{
  TestMethod(ShouldHandleStringContainsConstraint)
  {
    Assert::That("abcdef", Is().Containing("bcde"));
  }

  TestMethod(StringConstraintShouldHandleMatchAtBeginningOfString)
  {
    Assert::That("abcdef", Is().Containing("a"));
  }

  TestMethod(ShouldHandleStringStartingWithConstraint)
  {
    Assert::That("abcdef", Is().StartingWith("bbc"));
  }

  TestMethod(ShouldHandleStringEndingWithConstraint)
  {
    Assert::That("abcdef", Is().EndingWith("def"));
  }

  TestMethod(ShouldHandleOperatorsForStrings)
  {
    Assert::That("abcdef", Is().StartingWith("ab").And().EndingWith("ef"));
  }

  TestMethod(ShouldHandleStringsWithMultipleOperators)
  {
    Assert::That("abcdef", Is().StartingWith("ab").And().Not().EndingWith("qwqw"));
  }

  TestMethod(ShouldHandleOfLength)
  {
    Assert::That("12345", Is().OfLength(5));
  }

  TestMethod(ShouldHandleWeirdLongExpressions)
  {
    Assert::That("12345", Is().OfLength(5).And().StartingWith("123").And().Not().EndingWith("zyxxy"));
  }

  TestMethod(ShouldHandleStdStrings)
  {
    Assert::That("12345", Is().Containing(std::string("23")));
  }
};
