#include "igloo_self_test.h"
using namespace igloo;


struct HasStreamOp
{
  HasStreamOp(int id)
    : m_id(id)
  {
  }
 
  int m_id;
};
 
std::ostream& operator<<(std::ostream& stream, const HasStreamOp& a)
{
  stream << a.m_id;
  return stream;
}

bool operator==(const HasStreamOp& lhs, const HasStreamOp& rhs)
{
  return lhs.m_id == rhs.m_id;
}
 
struct NoStreamOp
{
  NoStreamOp(int id)
    : m_id(id)
  {
  }
 
  int m_id;
};

bool operator==(const NoStreamOp& lhs, const NoStreamOp& rhs)
{
  return lhs.m_id == rhs.m_id;
}

struct NoStreamOpButWithTraits
{
  NoStreamOpButWithTraits(int id)
    : m_id(id)
  {
  }
 
  int m_id;
};

bool operator==(const NoStreamOpButWithTraits& lhs, const NoStreamOpButWithTraits& rhs)
{
  return lhs.m_id == rhs.m_id;
}

inline std::string Stringize(const NoStreamOpButWithTraits& t)
{
  return Stringize(t.m_id);
}  

TestFixture(StringizeTests)
{
  TestMethod(ShouldHandleTypesWithStreamOperators)
  {
    HasStreamOp a(12);
    HasStreamOp b(13);
    AssertTestFails(Assert::That(a, Is().EqualTo(b)), "Expected: equal to 13\nActual: 12");
  }

  TestMethod(ShouldHandleTypesWithoutStreamOperators)
  {
    NoStreamOp a(12);
    NoStreamOp b(13);
    AssertTestFails(Assert::That(a, Is().EqualTo(b)), "Expected: equal to [unsupported type]\nActual: [unsupported type]");
  }

  TestMethod(ShouldHandleTypesWithTraits)
  {
    NoStreamOpButWithTraits a(12);
    NoStreamOpButWithTraits b(13);
    AssertTestFails(Assert::That(a, Is().EqualTo(b)), "Expected: equal to 13\nActual: 12");
  }
};
