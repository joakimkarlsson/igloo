#ifndef IGLOO_COLLECTIONOPERATOR_H
#define IGLOO_COLLECTIONOPERATOR_H

namespace igloo {
   struct CollectionOperator : public ConstraintOperator
   {
      template <typename ConstraintListType, typename ActualType>
      bool EvaluateElementAgainstRestOfExpression(ConstraintListType& list, const ActualType& actual)
      {
         ResultStack innerResult;
         OperatorStack innerOperators;

         EvaluateConstraintList(list.m_tail, innerResult, innerOperators, actual);        
         EvaluateAllOperatorsOnStack(innerOperators, innerResult);

         if(innerResult.empty())
         {
            throw InvalidExpressionException("The expression after an all operator does not yield any result");
         }

         return innerResult.top();
      }

      void PerformOperation(ResultStack&)
      {   
      }

      int Precedence()
      {
         return 1;
      }
   };
}

#endif
