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
  class LessThanConstraint : public Constraint<T> {
  public:

    LessThanConstraint(T expected) : Constraint<T>(expected)
    {
    }

    bool Evaluate(T actual) const
    {
      return actual < Constraint<T>::_expected;
    }

    std::string ExpectationText() const
    {
      std::ostringstream str;
      str << "less than " << Constraint<T>::_expected;
      return str.str();
    }
  };

}

#endif	/* _LESSTHANCONSTRAINT_H */

