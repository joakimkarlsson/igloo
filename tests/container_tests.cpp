#include "../igloo.h"

using igloo::Assert;

TestFixture(ContainerConstraints)
{
  TestMethod(ContainerConstraints, ShouldHandleVectorsContaining)
  {
    std::vector<int> v;
    v.push_back(43);
    v.push_back(12);

    Assert::That(v, Is().Containing(43));
  }
};
