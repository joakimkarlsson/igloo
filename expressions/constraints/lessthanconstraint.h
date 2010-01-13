#ifndef IGLOO_LESSTHANCONSTRAINT_H
#define	IGLOO_LESSTHANCONSTRAINT_H

namespace igloo {

  template <typename ExpectedType>
  class LessThanConstraint : public Constraint<ExpectedType>
  {
  public:

  LessThanConstraint(ExpectedType expected) : Constraint<ExpectedType>(expected)
  {
  }

    template <typename ActualType>
    bool Evaluate(const ActualType& actual) const
    {
      return actual < Constraint<ExpectedType>::m_expected;
    }

    void ToString(std::string& str) const
    {
      std::ostringstream stm;
      stm << "less than " << Constraint<ExpectedType>::m_expected;
      str += stm.str();
    }
  };

}

#endif

