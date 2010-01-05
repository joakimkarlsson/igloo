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

  template <typename ExpectedType>
    class EqualToConstraint : public Constraint<ExpectedType>
   {
   public:

      EqualToConstraint(ExpectedType expected) : Constraint<ExpectedType>(expected) {}

     template <typename ActualType>
      bool Evaluate(ActualType actual) const
      {
         return actual == Constraint<ExpectedType>::_expected;
      }

      void ToString(std::string& str) const
      {
         std::ostringstream stm;
         stm << "equal to " << Constraint<ExpectedType>::_expected;
         str += stm.str();
      }
   };
}
#endif

