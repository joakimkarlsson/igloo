#include "igloo_self_test.h"

using igloo::Assert;
using igloo::AssertionException;

TestFixture(ContainerConstraints)
{
  typedef std::vector<int> IntVector;

  void SetUp()
  {
    m_vector = std::auto_ptr<IntVector>(new IntVector());
    m_vector->push_back(123);
    m_vector->push_back(43);
    m_vector->push_back(25);
    m_vector->push_back(54);
  }

  TestMethod(ShouldHandleContainingForVectors)
  {
    const IntVector& v = *(m_vector.get());

    Assert::That(v, Is().Containing(43));
  }

  TestMethod(ShouldHandleOfLengthForVectors)
  {
    const IntVector& v = *(m_vector.get());

    Assert::That(v, Is().OfLength(4));
  }

  TestMethod(ShouldHandleFailingOfLengthForVectors)
  {
    const IntVector& v = *(m_vector.get());

    AssertTestFails(Assert::That(v, Is().OfLength(7)), "of length 7\nActual:");
  }

  std::auto_ptr<IntVector> m_vector;
};
