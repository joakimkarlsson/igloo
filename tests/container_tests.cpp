#include "igloo_self_test.h"

using namespace igloo;

namespace igloo {

  template< typename T >
  std::string Stringize(const std::vector<T>& t)
  {
     std::ostringstream stm;
     stm << "vector (size: " << t.size() << ")";
     return stm.str();
  }
}

TestFixture(ContainerConstraints)
{
  void SetUp()
  {
    m_vector.clear();
    m_vector.push_back(123);
    m_vector.push_back(43);
    m_vector.push_back(25);
    m_vector.push_back(54);
  }

  TestMethod(ShouldHandleContainingForVectors)
  {
    Assert::That(m_vector, Is().Containing(43));
  }

  TestMethod(ShouldHandleOfLengthForVectors)
  {
    Assert::That(m_vector, Is().OfLength(4));
  }

  TestMethod(ShouldHandleFailingOfLengthForVectors)
  {
    AssertTestFails(Assert::That(m_vector, Is().OfLength(7)), "of length 7\nActual:");
  }

  std::vector<int> m_vector;
};
