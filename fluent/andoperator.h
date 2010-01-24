#ifndef IGLOO_ANDOPERATOR_H
#define IGLOO_ANDOPERATOR_H

namespace igloo {
  
  struct AndOperator : public ConstraintOperator
  {
    template <typename ConstraintListType, typename ActualType>
    void evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
    {
      while(!operators.empty())
      {
        ConstraintOperator* op = operators.top();
        
        op->PerformOperation(result);
        
        operators.pop();
      }
      
      operators.push(this);
      
      EvaluateConstraintList(list.tail_, result, operators, actual);
    }
    
    void PerformOperation(ResultStack& result)
    {
      bool right = result.top();
      result.pop();
      bool left = result.top();
      result.pop();
      
      result.push(left && right);
    }
  };
  
}
#endif
