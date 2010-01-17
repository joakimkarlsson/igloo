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
    Assert::That(m_vector, Contains(43));
  }

	TestMethod(ShouldDetectFailingContains)
	{
		AssertTestFails(Assert::That(m_vector, Is().Containing(99)), "contains 99");
	}

  TestMethod(ShouldHandleOfLengthForVectors)
  {
    Assert::That(m_vector, HasLength(4));
  }

  TestMethod(ShouldHandleFailingOfLengthForVectors)
  {
    AssertTestFails(Assert::That(m_vector, Is().OfLength(7)), "of length 7\nActual:");
  }

  std::vector<int> m_vector;
};       

TestFixture(ContainerConstraintsExpressionTemplates)
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
    Assert::That(m_vector, Contains(43));
  }

	TestMethod(ShouldDetectFailingContains)
	{
		AssertTestFails(Assert::That(m_vector, Contains(99)), "contains 99");
	}

  TestMethod(ShouldHandleOfLengthForVectors)
  {
    Assert::That(m_vector, HasLength(4));
  }

  TestMethod(ShouldHandleFailingOfLengthForVectors)
  {
    AssertTestFails(Assert::That(m_vector, HasLength(7)), "of length 7\nActual:");
  }

  std::vector<int> m_vector;
};
