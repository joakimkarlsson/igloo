#ifndef IGLOO_ANDOPERATOR_H
#define IGLOO_ANDOPERATOR_H

namespace igloo {
  
  struct AndOperator : public ConstraintOperator
  {
    template <typename ConstraintListType, typename ActualType>
    void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
    {
      while(!operators.empty())
      {
        ConstraintOperator* op = operators.top();
        
        op->PerformOperation(result);
        
        operators.pop();
      }
      
      operators.push(this);
      
      EvaluateConstraintList(list.m_tail, result, operators, actual);
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
