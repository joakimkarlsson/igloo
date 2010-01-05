/* 
 * File:   greaterthanconstraint.h
 * Author: joakim
 *
 * Created on December 18, 2009, 7:17 PM
 */

#ifndef _GREATERTHANCONSTRAINT_H
#define	_GREATERTHANCONSTRAINT_H

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
#endif	/* _GREATERTHANCONSTRAINT_H */

