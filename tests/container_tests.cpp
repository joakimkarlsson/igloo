#include "../igloo.h"

using igloo::Assert;

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

  TestMethod(ContainerConstraints, ShouldHandleContainingForVectors)
  {
    const IntVector& v = *(m_vector.get());

    Assert::That(v, Is().Containing(43));
  }

  TestMethod(ContainerConstraints, ShouldHandleOfLengthForVectors)
  {
    const IntVector& v = *(m_vector.get());

    Assert::That(v, Is().OfLength(4));
  }

  std::auto_ptr<IntVector> m_vector;
};
