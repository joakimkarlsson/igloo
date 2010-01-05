/* 
 * File:   lessthanconstraint.h
 * Author: joakim
 *
 * Created on December 18, 2009, 11:24 PM
 */

#ifndef _LESSTHANCONSTRAINT_H
#define	_LESSTHANCONSTRAINT_H

namespace igloo {

  template <typename ExpectedType>
  class LessThanConstraint : public Constraint<ExpectedType>
  {
  public:

  LessThanConstraint(ExpectedType expected) : Constraint<ExpectedType>(expected)
  {
  }

    template <typename ActualType>
    bool Evaluate(ActualType actual) const
    {
      return actual < Constraint<ExpectedType>::_expected;
    }

    void ToString(std::string& str) const
    {
      std::ostringstream stm;
      stm << "less than " << Constraint<ExpectedType>::_expected;
      str += stm.str();
    }
  };

}

#endif	/* _LESSTHANCONSTRAINT_H */

