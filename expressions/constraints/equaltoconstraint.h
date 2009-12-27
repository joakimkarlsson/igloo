/* 
* File:   equaltooperator.h
* Author: joakim
*
* Created on December 13, 2009, 11:13 AM
*/

#ifndef _EQUALTOCONSTRAINT_H
#define	_EQUALTOCONSTRAINT_H

#include "constraint.h"

namespace igloo {

  template <typename T>
    class EqualToConstraint : public Constraint<T>, public IEvaluateConstraint<T>
   {
   public:

      EqualToConstraint(T expected) : Constraint<T>(expected)
      {
      }

      bool Evaluate(T actual) const
      {
         return actual == Constraint<T>::_expected;
      }

      std::string ExpectationText() const
      {
         std::ostringstream str;
         str << "equal to " << Constraint<T>::_expected;
         return str.str();
      }
   };
}
#endif

