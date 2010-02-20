#ifndef IGLOO_COLLECTIONCONSTRAINTEVALUATOR_H
#define IGLOO_COLLECTIONCONSTRAINTEVALUATOR_H

namespace igloo {

  template <typename ConstraintListType, typename ActualType>
  struct CollectionConstraintEvaluator
  {
    static unsigned int Evaluate(const ConstraintOperator& op, ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
    {
      ConstraintOperator::EvaluateOperatorsWithLessOrEqualPrecedence(op, operators, result);

      unsigned int passed_elements = 0;
      typename ActualType::const_iterator it;
      for(it = actual.begin(); it != actual.end(); it++)
      {
         if(ConstraintOperator::EvaluateElementAgainstRestOfExpression(list, *it))
         {
           passed_elements++;
         }
      }

      return passed_elements;
    }
  };

}

#endif
