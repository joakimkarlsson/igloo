#ifndef IGLOO_EXPRESSIONBUILDER_H
#define IGLOO_EXPRESSIONBUILDER_H

namespace igloo {
  
  typedef ConstraintList<AllOperator, Nil> AllOperatorNode;
  typedef ConstraintList<AndOperator, Nil> AndOperatorNode;
  
  
  template <typename ConstraintListType>
  struct ExpressionBuilder
  {
    ExpressionBuilder(const ConstraintListType& list) : m_constraint_list(list)
    {
    }
    
    template <typename ExpectedType>
    ExpressionBuilder<typename type_concat<ConstraintListType, ConstraintList<ConstraintAdapter<EqualsConstraint<ExpectedType> >, Nil> >::t> 
      EqualTo(const ExpectedType& expected)
    {
      typedef ExpressionBuilder< typename type_concat<ConstraintListType, ConstraintList<ConstraintAdapter<EqualsConstraint<ExpectedType> >, Nil> >::t > builder_type;
      ConstraintAdapter<EqualsConstraint<ExpectedType> > constraint(expected);
      ConstraintList<ConstraintAdapter<EqualsConstraint<ExpectedType> >, Nil> node(constraint, Nil());
      return builder_type(concat(m_constraint_list, node));
    }
    
    ExpressionBuilder<typename type_concat<ConstraintListType, AllOperatorNode>::t> All()
    {
      typedef ExpressionBuilder<typename type_concat<ConstraintListType, AllOperatorNode>::t> builder_type;
      AllOperator op;
      AllOperatorNode node(op, Nil());
      return builder_type(concat(m_constraint_list, node));
    }
    
    ExpressionBuilder<typename type_concat<ConstraintListType, AndOperatorNode>::t> And()
    {
      ExpressionBuilder<typename type_concat<ConstraintListType, AndOperatorNode>::t> builder_type;
      AndOperator op;
      AndOperatorNode node(op, Nil());
      return builder_type(concat(m_constraint_list, node));
    }
    
    template <typename ActualType>
    void Evaluate(ResultStack& result, OperatorStack& operators, const ActualType& actual)
    {
      EvaluateConstraintList(m_constraint_list, result, operators, actual);
    }
    
    ConstraintListType m_constraint_list;
  };
  
}

#endif
