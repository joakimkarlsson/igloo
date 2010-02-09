#ifndef IGLOO_NONEOPERATOR_H
#define IGLOO_NONEOPERATOR_H

namespace igloo {

   struct NoneOperator : public CollectionOperator
   {
      template <typename ConstraintListType, typename ActualType>
      void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
      {
         EvaluateOperatorsWithLessOrEqualPrecedence(operators, result);

         bool evaluation_result = true;
         typename ActualType::const_iterator it;
         for(it = actual.begin(); it != actual.end(); it++)
         {
            if(EvaluateElementAgainstRestOfExpression(list, *it))
            {
               evaluation_result = false;
               break;
            }
         }

         result.push(evaluation_result); 
      }
   };

   template<>
   struct Stringizer<NoneOperator>
   {
      static std::string ToString(const NoneOperator&)
      {
         return "none";
      }
   };

}

#endif
