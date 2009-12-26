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
  class GreaterThanConstraint : public Constraint<T> {
  public:

    GreaterThanConstraint(T expected) : Constraint<T>(expected)
    {
    }

    bool Evaluate(T actual) const
    {
      return actual > Constraint<T>::_expected;
    }

    std::string ExpectationText() const
    {
      std::ostringstream str;
      str << "greater than " << Constraint<T>::_expected;
      return str.str();
    }
  };

}
#endif	/* _GREATERTHANCONSTRAINT_H */

