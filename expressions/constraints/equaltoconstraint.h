#ifndef IGLOO_EQUALTOCONSTRAINT_H
#define	IGLOO_EQUALTOCONSTRAINT_H

#include "constraint.h"
#include "../../stringize.h"

namespace igloo {

  template <typename ExpectedType>
    class EqualToConstraint : public Constraint<ExpectedType>
   {
   public:

      EqualToConstraint(ExpectedType expected) : Constraint<ExpectedType>(expected) {}

     template <typename ActualType>
      bool Evaluate(const ActualType& actual) const
      {
         return actual == Constraint<ExpectedType>::m_expected;
      }

      void ToString(std::string& str) const
      {
         std::ostringstream stm;
         stm << "equal to " << stringize_trait<ExpectedType>::Stringize(Constraint<ExpectedType>::m_expected);
         str += stm.str();
      }
   };
}
#endif

