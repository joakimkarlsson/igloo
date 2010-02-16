
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

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
    Assert::That("abcdef", StartsWith("abc"));
  }

  TestMethod(ShouldHandleStringEndingWithConstraint)
  {
    Assert::That("abcdef", EndsWith("def"));
  }

  TestMethod(ShouldHandleOperatorsForStrings)
  {
    Assert::That("abcdef", StartsWith("ab") && EndsWith("ef"));
  }

  TestMethod(ShouldHandleStringsWithMultipleOperators)
  {
    Assert::That("abcdef", StartsWith("ab") && !EndsWith("qwqw"));
  }

  TestMethod(ShouldHandleOfLength)
  {
    Assert::That("12345", HasLength(5));
  }

  TestMethod(ShouldHandleWeirdLongExpressions)
  {
    Assert::That("12345", HasLength(5) && StartsWith("123") && !EndsWith("zyxxy"));
  }

  TestMethod(ShouldHandleStdStrings)
  {
    Assert::That("12345", Contains(std::string("23")));
  }

  TestMethod(ShouldHandleSimpleChar)
  {
    Assert::That("12345", StartsWith('1'));
  }
};
