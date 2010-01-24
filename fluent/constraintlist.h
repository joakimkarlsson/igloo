#ifndef IGLOO_CONSTRAINT_H
#define IGLOO_CONSTRAINT_H

namespace igloo {
  
  class ConstraintOperator;
  typedef std::stack<bool> ResultStack;
  typedef std::stack<ConstraintOperator*> OperatorStack;

  template <typename HT, typename TT>
  struct ConstraintList
  {
    typedef HT HeadType;
    typedef TT TailType;
    
    ConstraintList(const HeadType& head, const TailType& tail) 
    : m_head(head), m_tail(tail)
    {
    }
    
    HeadType m_head;
    TailType m_tail;
  };
  
  struct Nil 
  {
    Nil() {}
    Nil(const Nil&) {}
  };
  

  // ---- List concatenation
  
  template <typename L1, typename L2>
  struct type_concat
  {
    typedef ConstraintList<typename L1::HeadType, typename type_concat<typename L1::TailType, L2>::t> t;
  };
  
  template <typename L2> struct type_concat<Nil, L2> { typedef L2 t; };
  
  template <typename L3> inline L3 tr_concat(const Nil&, const Nil&) { return Nil(); }    
  
  template <typename L1, typename L2, typename L3>
  inline L3 tr_concat(const Nil& a, const L2& b)
  {
    return L3(b.m_head, tr_concat<typename type_concat<Nil, typename L2::TailType>::t>(a, b.m_tail));
  }
    
  template <typename L1, typename L2, typename L3>
  inline L3 tr_concat(const L1& a, const L2& b)
  {
    return L3(a.m_head, tr_concat<typename L1::TailType, L2, typename type_concat< typename L1::TailType, L2>::t>(a.m_tail, b));
  }  
  
  template <typename L1, typename L2>
  inline typename type_concat<L1, L2>::t concat(const L1& list1, const L2& list2)
  {
    return tr_concat<L1, L2, typename type_concat<L1, L2>::t>(list1, list2);
  }
              
  // ---- Evaluation of list of constraints
  
  template <typename ConstraintListType, typename ActualType> 
  inline void EvaluateConstraintList(ConstraintListType& constraint_list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
  {
    constraint_list.m_head.Evaluate(constraint_list, result, operators, actual);
  }
  
  template <typename ActualType>
  inline void EvaluateConstraintList(Nil&, ResultStack&, OperatorStack&, const ActualType&) {}

}

#endif
