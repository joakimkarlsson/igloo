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
  
  template <typename LeftList, typename RightList, typename ResultList>
  struct ListConcat
  {
    static ResultList Concatenate(const LeftList& left, const RightList& right)
    {
      return ResultList(left.m_head, ListConcat<LeftList::TailType, RightList, typename type_concat< typename LeftList::TailType, RightList>::t>::Concatenate(left.m_tail, right));
    }
  };
  
  // Concatenating an empty list with a second list yields the second list
  template <typename RightList, typename ResultList>
  struct ListConcat<Nil, RightList, ResultList>
  {
    static ResultList Concatenate(const Nil& left, const RightList& right)
    {
      return ResultList(right.m_head, ListConcat<Nil, RightList::TailType, typename type_concat<Nil, RightList::TailType>::t>::Concatenate(left, right.m_tail));
    }
    
  };
   
  // Concatenating two empty lists yields an empty list
  template <typename ResultList>
  struct ListConcat<Nil, Nil, ResultList>
  {
    static ResultList Concatenate(const Nil& left, const Nil& right)
    {
      return Nil();
    }
  }; 
  
  template <typename L1, typename L2>
  inline typename type_concat<L1, L2>::t Concatenate(const L1& list1, const L2& list2)
  {
    return ListConcat<L1, L2, typename type_concat<L1, L2>::t>::Concatenate(list1, list2);
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
