#ifndef IGLOO_ALLOPERATOR_H
#define IGLOO_ALLOPERATOR_H

#include "collectionoperator.h"

namespace igloo {

   struct AllOperator : public CollectionOperator
   {
      template <typename ConstraintListType, typename ActualType>
      void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
      {
         EvaluateOperatorsWithLessOrEqualPrecedence(operators, result);

         bool evaluation_result = true;
         typename ActualType::const_iterator it;
         for(it = actual.begin(); it != actual.end(); it++)
         {
            if(!EvaluateElementAgainstRestOfExpression(list, *it))
            {
               evaluation_result = false;
               break;
            }
         }

         result.push(evaluation_result); 
      }
   };

   inline std::string Stringize(const AllOperator&)
   {
      return "all";
   }

}

#endif
