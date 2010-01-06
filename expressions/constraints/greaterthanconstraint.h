#ifndef IGLOO_GREATERTHANCONSTRAINT_H
#define	IGLOO_GREATERTHANCONSTRAINT_H

namespace igloo {

  template <typename ExpectedType>
  class GreaterThanConstraint : public Constraint<ExpectedType>
  {
  public:

    GreaterThanConstraint(ExpectedType expected) : Constraint<ExpectedType>(expected) {}

    template <typename ActualType>
    bool Evaluate(ActualType actual) const
    {
      return actual > Constraint<ExpectedType>::_expected;
    }

    void ToString(std::string& str) const
    {
      std::ostringstream stm;
      stm << "greater than " << Constraint<ExpectedType>::_expected;
      str += stm.str();
    }
  };

}
#endif

