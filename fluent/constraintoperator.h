#ifndef IGLOO_CONTRAINTOPERATOR_H
#define IGLOO_CONTRAINTOPERATOR_H

namespace igloo {
  
  struct ConstraintOperator
  {
    virtual void PerformOperation(ResultStack& result) = 0;
    virtual int Precedence() = 0;
    
  protected:
    void EvaluateOperatorsWithLessOrEqualPrecedence(OperatorStack& operators, ResultStack& result)
    {
      while(!operators.empty())
      {
        ConstraintOperator* op = operators.top();
        
        if(op->Precedence() > Precedence())
        {
          break;
        }
        
        op->PerformOperation(result);        
        operators.pop();
      }      
    }
    
    static void EvaluateAllOperatorsOnStack(OperatorStack& operators, ResultStack& result)
    {
      while(!operators.empty())
      {
        ConstraintOperator* op = operators.top();
        op->PerformOperation(result);        
        operators.pop();
      } 
    }
  };
  
  struct Noop
  {
    Noop() {}
    Noop(const Noop&) {}
    template <typename ConstraintListType, typename ActualType> 
    void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual) 
    {
      EvaluateConstraintList(list.m_tail, result, operators, actual);
    }
  };
  
  inline std::string Stringize(const Noop&)
  {
    return "";
  }  
  
  struct InvalidExpressionException
  {
    InvalidExpressionException(const std::string& message) : m_message(message)
    {
    }
    
    const std::string& Message() const
    {
      return m_message;
    }
    
    std::string m_message;
  };
  
}

#endif
