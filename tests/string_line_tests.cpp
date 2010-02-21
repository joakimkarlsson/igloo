#include <tests/igloo_self_test.h>
using namespace igloo;

TestFixture(StringLineTests)
{
  TestMethod(CanAssertThatAtLeastOneLineInAStreamMatches)
  {
    Assert::That("First line\n", Has().AtLeast(1).EqualTo("First line"));
  }

  TestMethod(CanDetectWhenAssertionFails)
  {
    AssertTestFails(Assert::That("First line\n", Has().AtLeast(1).EqualTo("Second line")), "Expected: at least 1 equal to Second line");
  }

  TestMethod(CanHandleLineMissingNewline)
  {
    Assert::That("First line", Has().AtLeast(1).EqualTo("First line"));
  }

  TestMethod(CanHandleSeveralLines)
  {
    std::string lines = "First line\nSecond line";
    Assert::That(lines, Has().Exactly(2).EndingWith("line"));
  }
};
