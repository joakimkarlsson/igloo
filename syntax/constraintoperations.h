#ifndef IGLOO_CONSTRAINTOPERATIONS_H
#define IGLOO_CONSTRAINTOPERATIONS_H

#include "syntaxtree/node.h"

namespace igloo {

template <typename ExpressionItemType>
class UnaryNode;

template <typename ExpressionItemType>
class BinaryNode;

template <typename ExpressionItemType>
class ConstraintNode;


  template <typename ExpressionItemType>
  class ConstraintOperations : public Node<ExpressionItemType>
  {
  public:
    typedef Node<ExpressionItemType> Base;

    explicit ConstraintOperations(std::auto_ptr<ExpressionItemType> expressionItem) : Base(expressionItem) {}

    template <typename ExpectedType>
      ConstraintNode<ExpressionItem<EqualToConstraint<ExpectedType>, ExpressionItemType> > EqualTo(ExpectedType expected)
    {
      typedef ExpressionItem<EqualToConstraint<ExpectedType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<EqualToConstraint<ExpectedType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new EqualToConstraint<ExpectedType>(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<EqualToConstraint<std::string>, ExpressionItemType> > EqualTo(const char* expected)
    {
      typedef ExpressionItem<EqualToConstraint<std::string>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<EqualToConstraint<std::string> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new EqualToConstraint<std::string>(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    template <typename ExpectedType>
    ConstraintNode<ExpressionItem<GreaterThanConstraint<ExpectedType>, ExpressionItemType> > GreaterThan(ExpectedType expected)
    {
      typedef ExpressionItem<GreaterThanConstraint<ExpectedType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<GreaterThanConstraint<ExpectedType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new GreaterThanConstraint<ExpectedType>(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    template <typename ExpectedType>
      ConstraintNode<ExpressionItem<LessThanConstraint<ExpectedType>, ExpressionItemType> > LessThan(ExpectedType expected)
    {
      typedef ExpressionItem<LessThanConstraint<ExpectedType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<LessThanConstraint<ExpectedType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new LessThanConstraint<ExpectedType>(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<StringContainingConstraint, ExpressionItemType> > Containing(std::string expected)
    {
      typedef ExpressionItem<StringContainingConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringContainingConstraint> Constraint_ptr;
 
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringContainingConstraint(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<StringStartingWithConstraint, ExpressionItemType> > StartingWith(std::string expected)
    {
      typedef ExpressionItem<StringStartingWithConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringStartingWithConstraint> Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringStartingWithConstraint(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<StringEndingWithConstraint, ExpressionItemType> > EndingWith(std::string expected)
    {
      typedef ExpressionItem<StringEndingWithConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringEndingWithConstraint> Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringEndingWithConstraint(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

   ConstraintNode<ExpressionItem<StringOfLengthConstraint, ExpressionItemType> > OfLength(int expected)
    {
      typedef ExpressionItem<StringOfLengthConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringOfLengthConstraint> Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringOfLengthConstraint(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

  };
}

#endif
