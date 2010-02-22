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

  TestMethod(CanHandleWindowsLineEndings)
  {
    std::string lines = "First line\r\nSecond line\r\nThird line";
    Assert::That(lines, Has().Exactly(3).EndingWith("line"));
  }

  TestMethod(CanMatchBeginningOfLinesWithWindowsLineEndings)
  {
    std::string lines = "First line\r\nSecond line\r\nThird line";
    Assert::That(lines, Has().Exactly(1).StartingWith("Second"));
  }

  TestMethod(CanHandleEmptyLinesWhenUsingWindowsLineEndings)
  {
    std::string lines = "\r\nSecond line\r\n\r\n";
    Assert::That(lines, Has().Exactly(2).OfLength(0));
  }

  TestMethod(CanHandleLastLineMissingNewlineForWindowsLineEndings)
  {
    std::string lines = "First line\r\nSecond line";
    Assert::That(lines, Has().Exactly(2).EndingWith("line"));
  }

  TestMethod(CanHandleAllEmptyLines)
  {
    Assert::That("\n\n\n\n\n\n", Has().Exactly(6).OfLength(0));
  }

  TestMethod(CanHandleAllEmptyLinesWithWindowsLineEndings)
  {
    Assert::That("\r\n\r\n\r\n", Has().Exactly(3).OfLength(0));
  }
};
