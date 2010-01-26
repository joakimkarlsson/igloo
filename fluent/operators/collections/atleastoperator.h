#ifndef IGLOO_ATLEASTOPERATOR_H
#define IGLOO_ATLEASTOPERATOR_H

#include "collectionoperator.h"

namespace igloo {

   struct AtLeastOperator : public CollectionOperator
   {
      AtLeastOperator(unsigned int expected) : m_expected(expected) {}

      template <typename ConstraintListType, typename ActualType>
      void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
      {
         EvaluateOperatorsWithLessOrEqualPrecedence(operators, result);

         unsigned int passed_elements = 0;
         typename ActualType::const_iterator it;
         for(it = actual.begin(); it != actual.end(); it++)
         {
            if(EvaluateElementAgainstRestOfExpression(list, *it))
            {
               passed_elements++;
            }
         }

         result.push(passed_elements >= m_expected); 
      }

      unsigned int m_expected;
   };

   inline std::string Stringize(const AtLeastOperator& op)
   {
      std::ostringstream stm;
      stm << "at least " << op.m_expected;
      return stm.str();
   }

}

#endif