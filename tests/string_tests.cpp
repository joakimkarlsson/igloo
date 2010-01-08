#include "../igloo.h"

using igloo::Assert;

TestFixture(Strings)
{
  TestMethod(Strings, ShouldHandleStringContainsConstraint)
  {
    Assert::That("abcdef", Is().Containing("bcde"));
  }

  TestMethod(Strings, StringConstraintShouldHandleMatchAtBeginningOfString)
  {
    Assert::That("abcdef", Is().Containing("a"));
  }

  TestMethod(Strings, ShouldHandleStringStartingWithConstraint)
  {
    Assert::That("abcdef", Is().StartingWith("abc"));
  }

  TestMethod(Strings, ShouldHandleStringEndingWithConstraint)
  {
    Assert::That("abcdef", Is().EndingWith("def"));
  }

  TestMethod(Strings, ShouldHandleOperatorsForStrings)
  {
    Assert::That("abcdef", Is().StartingWith("ab").And().EndingWith("ef"));
  }

  TestMethod(Strings, ShouldHandleStringsWithMultipleOperators)
  {
    Assert::That("abcdef", Is().StartingWith("ab").And().Not().EndingWith("qwqw"));
  }

  TestMethod(Strings, ShouldHandleOfLength)
  {
    Assert::That("12345", Is().OfLength(5));
  }

  TestMethod(Strings, ShouldHandleWeirdLongExpressions)
  {
    Assert::That("12345", Is().OfLength(5).And().StartingWith("123").And().Not().EndingWith("zyxxy"));
  }

  TestMethod(Strings, ShouldHandleStdStrings)
  {
    Assert::That("12345", Is().Containing(std::string("23")));
  }
};
