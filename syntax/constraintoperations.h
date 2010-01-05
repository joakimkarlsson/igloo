#ifndef IGLOO_CONSTRAINTOPERATIONS_H
#define IGLOO_CONSTRAINTOPERATIONS_H

#include "syntaxtree/iexpressionowner.h"
#include "syntaxtree/node.h"

namespace igloo {

  template <typename ExpressionItemType>
  class ConstraintOperations : public Node<ExpressionItemType>
  {
  public:
    explicit ConstraintOperations(std::auto_ptr<ExpressionItemType> expressionItem) : Node<ExpressionItemType>(expressionItem) {}

    template <typename OperandType>
      ConstraintNode<ConstraintOperations, ExpressionItem<OperandType, ExpressionItemType> > EqualTo(OperandType expected)
    {
      typedef ExpressionItem<OperandType, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<Constraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new EqualToConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<ConstraintOperations, ExpressionItem<OperandType, ExpressionItemType> >(expressionItem);
    }

    ConstraintNode<ConstraintOperations, ExpressionItem<std::string, ExpressionItemType> > EqualTo(const char* expected)
    {
      return EqualTo<std::string>(std::string(expected));
    }

    template <typename OperandType>
    ConstraintNode<ConstraintOperations, ExpressionItem<OperandType, ExpressionItemType> > GreaterThan(OperandType expected)
    {
      typedef ExpressionItem<OperandType, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<Constraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new GreaterThanConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<ConstraintOperations, ExpressionItem<OperandType, ExpressionItemType> >(expressionItem);
    }

    template <typename OperandType>
      ConstraintNode<ConstraintOperations, ExpressionItem<OperandType, ExpressionItemType> > LessThan(OperandType expected)
    {
      typedef ExpressionItem<OperandType, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<Constraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new LessThanConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<ConstraintOperations, ExpressionItem<OperandType, ExpressionItemType> >(expressionItem);
    }
  };

}

#endif
