/* 
 * File:   lessthanconstraint.h
 * Author: joakim
 *
 * Created on December 18, 2009, 11:24 PM
 */

#ifndef _LESSTHANCONSTRAINT_H
#define	_LESSTHANCONSTRAINT_H

namespace igloo {

  template <typename T>
  class LessThanConstraint : public Constraint<T>, public IEvaluateConstraint<T>
  {
  public:

  LessThanConstraint(T expected) : Constraint<T>(expected)
  {
  }

    bool Evaluate(T actual) const
    {
      return actual < Constraint<T>::_expected;
    }

    void ToString(std::string& str) const
    {
      std::ostringstream stm;
      stm << "less than " << Constraint<T>::_expected;
      str += stm.str();
    }
  };

}

#endif	/* _LESSTHANCONSTRAINT_H */

