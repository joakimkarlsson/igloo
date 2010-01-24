#ifndef IGLOO_CONTRAINTOPERATOR_H
#define IGLOO_CONTRAINTOPERATOR_H

namespace igloo {
  
  struct ConstraintOperator
  {
    virtual void PerformOperation(ResultStack& result) = 0;
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
  
}

#endif
