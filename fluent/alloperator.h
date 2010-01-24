#ifndef IGLOO_ALLOPERATOR_H
#define IGLOO_ALLOPERATOR_H

namespace igloo {

  struct AllOperator : public ConstraintOperator
  {
    template <typename ConstraintListType, typename ActualType>
    void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
    {
      EvaluateOperatorsWithLessOrEqualPrecedence(operators, result);
      
      bool evaluation_result = true;
      typename ActualType::const_iterator it;
      for(it = actual.begin(); it != actual.end(); it++)
      {
        ResultStack innerResult;
        OperatorStack innerOperators;
        
        EvaluateConstraintList(list.m_tail, innerResult, innerOperators, *it);
        
        EvaluateAllOperatorsOnStack(innerOperators, innerResult);
        
        if(!innerResult.top())
        {
          evaluation_result = false;
          break;
        }
        
      }
      
      result.push(evaluation_result); 
    }
    
    void PerformOperation(ResultStack& result)
    {   
    }
    
    int Precedence()
    {
      return 1;
    }
  };
  
  inline std::string Stringize(const AllOperator&)
  {
    return "all";
  }
  
}

#endif
