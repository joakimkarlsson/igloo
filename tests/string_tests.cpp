#include "igloo_self_test.h"

using namespace igloo;

TestFixture(Strings)
{
  TestMethod(ShouldHandleStringContainsConstraint)
  {
    Assert::That("abcdef", Contains("bcde"));
  }

  TestMethod(StringConstraintShouldHandleMatchAtBeginningOfString)
  {
    Assert::That("abcdef", Contains("a"));
  }  

	TestMethod(ShouldDetectFailingContains)
	{
		AssertTestFails(Assert::That("abcdef", Contains("hello")), "contains hello");
	}

  TestMethod(ShouldHandleStringStartingWithConstraint)
  {
    Assert::That("abcdef", Is().StartingWith("abc"));
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
