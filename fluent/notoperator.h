#ifndef IGLOO_NOTOPERATOR_H
#define IGLOO_NOTOPERATOR_H

namespace igloo {
  
  struct NotOperator : public ConstraintOperator
  {
    template <typename ConstraintListType, typename ActualType>
    void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
    {
      EvaluateOperatorsWithLessOrEqualPrecedence(operators, result);   

      operators.push(this);
      
      EvaluateConstraintList(list.m_tail, result, operators, actual);
    }
    
    void PerformOperation(ResultStack& result)
    {
      bool right = result.top();
      result.pop();
            
      result.push(!right);
    }
    
    int Precedence()
    {
      return 2;
    }
  };
  
  inline std::string Stringize(const NotOperator&)
  {
    return "not";
  }
}
#endif
