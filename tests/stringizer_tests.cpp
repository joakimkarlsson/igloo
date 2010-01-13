#include "igloo_self_test.h"
using namespace igloo;

TestFixture(StringizerTests)
{
  TestMethod(ShouldHandleSimpleLiterals)
  {
    Assert::That(Stringize(56), Is().EqualTo("56"));
  }
};
