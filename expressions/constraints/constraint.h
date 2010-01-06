#ifndef IGLOO_CONSTRAINT_H
#define	IGLOO_CONSTRAINT_H

namespace igloo {

  template <typename ExpectedType>
  class Constraint
  {
  public:

  Constraint(ExpectedType expected) : _expected(expected) {}

  protected:
    ExpectedType _expected;
  };
}
#endif

