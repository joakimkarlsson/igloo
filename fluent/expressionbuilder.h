#ifndef IGLOO_EXPRESSIONBUILDER_H
#define IGLOO_EXPRESSIONBUILDER_H

namespace igloo {
  
  template <typename ConstraintListType>
  struct ExpressionBuilder
  {
    ExpressionBuilder(const ConstraintListType& list) : m_constraint_list(list)
    {
    }
    
    template <typename ExpectedType>
    ExpressionBuilder<typename type_concat<ConstraintListType, ConstraintList<ConstraintAdapter<EqualsConstraint<ExpectedType> >, Nil> >::t > 
      EqualTo(const ExpectedType& expected)
    {
      typedef ExpressionBuilder< typename type_concat<ConstraintListType, ConstraintList<ConstraintAdapter<EqualsConstraint<ExpectedType> >, Nil> >::t > builder_type;
      ConstraintAdapter<EqualsConstraint<ExpectedType> > constraint(expected);
      ConstraintList<ConstraintAdapter<EqualsConstraint<ExpectedType> >, Nil> list(constraint, Nil());
      return builder_type(concat(m_constraint_list, list));
    }
    
    ExpressionBuilder<typename type_concat<ConstraintListType, ConstraintList<AllOperator, Nil> >::t> All()
    {
      typedef ExpressionBuilder<typename type_concat<ConstraintListType, ConstraintList<AllOperator, Nil> >::t> builder_type;
      AllOperator op;
      ConstraintList<AllOperator, Nil> list(op, Nil());
      return builder_type(concat(m_constraint_list, list));
    }
    
    ExpressionBuilder<typename type_concat<ConstraintListType, ConstraintList<AndOperator, Nil> >::t> And()
    {
      ExpressionBuilder<typename type_concat<ConstraintListType, ConstraintList<AndOperator, Nil> >::t> builder_type;
      AndOperator op;
      ConstraintList<AndOperator, Nil> list(op, Nil());
      return builder_type(concat(m_constraint_list, list));
    }
    
    template <typename ActualType>
    void evaluate(ResultStack& result, OperatorStack& operators, const ActualType& actual)
    {
      evaluate_list(m_constraint_list, result, operators, actual);
    }
    
    ConstraintListType m_constraint_list;
  };
  
}

#endif
