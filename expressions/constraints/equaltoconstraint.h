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

      virtual void ToString(std::string str) const
      {
         std::ostringstream stm;
         stm << "equal to " << Constraint<T>::_expected;
         str += stm.str();
      }
   };
}
#endif

