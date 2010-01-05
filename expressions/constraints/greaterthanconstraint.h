/* 
 * File:   greaterthanconstraint.h
 * Author: joakim
 *
 * Created on December 18, 2009, 7:17 PM
 */

#ifndef _GREATERTHANCONSTRAINT_H
#define	_GREATERTHANCONSTRAINT_H

namespace igloo {

  template <typename T>
  class GreaterThanConstraint : public Constraint<T>, public IEvaluateConstraint<T>
  {
  public:

    GreaterThanConstraint(T expected) : Constraint<T>(expected)
    {
    }

    bool Evaluate(T actual) const
    {
      return actual > Constraint<T>::_expected;
    }

    void ToString(std::string& str) const
    {
      std::ostringstream stm;
      stm << "greater than " << Constraint<T>::_expected;
      str += stm.str();
    }
  };

}
#endif	/* _GREATERTHANCONSTRAINT_H */

