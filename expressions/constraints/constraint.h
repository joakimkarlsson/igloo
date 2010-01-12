#ifndef IGLOO_CONSTRAINT_H
#define	IGLOO_CONSTRAINT_H

namespace igloo {

  template <typename ExpectedType>
  class Constraint
  {
  public:

  Constraint(ExpectedType expected) : m_expected(expected) {}

  protected:
    ExpectedType m_expected;
  };
}
#endif

