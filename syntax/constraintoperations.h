#ifndef IGLOO_CONSTRAINTOPERATIONS_H
#define IGLOO_CONSTRAINTOPERATIONS_H

#include "syntaxtree/node.h"

namespace igloo {

  template <typename ExpressionItemType>
  class ConstraintOperations : public Node<ExpressionItemType>
  {
  public:
    explicit ConstraintOperations(std::auto_ptr<ExpressionItemType> expressionItem) : Node<ExpressionItemType>(expressionItem) {}

    template <typename OperandType>
      ConstraintNode<ExpressionItem<EqualToConstraint<OperandType>, ExpressionItemType> > EqualTo(OperandType expected)
    {
      typedef ExpressionItem<EqualToConstraint<OperandType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<EqualToConstraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new EqualToConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<EqualToConstraint<std::string>, ExpressionItemType> > EqualTo(const char* expected)
    {
      typedef ExpressionItem<EqualToConstraint<std::string>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<EqualToConstraint<std::string> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new EqualToConstraint<std::string>(expected)), Node<ExpressionItemType>::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    template <typename OperandType>
    ConstraintNode<ExpressionItem<GreaterThanConstraint<OperandType>, ExpressionItemType> > GreaterThan(OperandType expected)
    {
      typedef ExpressionItem<GreaterThanConstraint<OperandType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<GreaterThanConstraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new GreaterThanConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    template <typename OperandType>
      ConstraintNode<ExpressionItem<LessThanConstraint<OperandType>, ExpressionItemType> > LessThan(OperandType expected)
    {
      typedef ExpressionItem<LessThanConstraint<OperandType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<LessThanConstraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new LessThanConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<StringContainingConstraint, ExpressionItemType> > Containing(std::string expected)
    {
      typedef ExpressionItem<StringContainingConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringContainingConstraint> Constraint_ptr;
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringContainingConstraint(expected)), Node<ExpressionItemType>::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<StringStartingWithConstraint, ExpressionItemType> > StartingWith(std::string expected)
    {
      typedef ExpressionItem<StringStartingWithConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringStartingWithConstraint> Constraint_ptr;
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringStartingWithConstraint(expected)), Node<ExpressionItemType>::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<StringEndingWithConstraint, ExpressionItemType> > EndingWith(std::string expected)
    {
      typedef ExpressionItem<StringEndingWithConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringEndingWithConstraint> Constraint_ptr;
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringEndingWithConstraint(expected)), Node<ExpressionItemType>::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

   ConstraintNode<ExpressionItem<StringOfLengthConstraint, ExpressionItemType> > OfLength(int expected)
    {
      typedef ExpressionItem<StringOfLengthConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringOfLengthConstraint> Constraint_ptr;
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringOfLengthConstraint(expected)), Node<ExpressionItemType>::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

  };
}

#endif
