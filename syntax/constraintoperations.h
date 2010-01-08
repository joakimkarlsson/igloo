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

    template <typename ExpectedType>
    ConstraintNode<ExpressionItem<ContainingConstraint<ExpectedType>, ExpressionItemType> > Containing(ExpectedType expected)
    {
      typedef ExpressionItem<ContainingConstraint<ExpectedType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<ContainingConstraint<ExpectedType> > Constraint_ptr;
 
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new ContainingConstraint<ExpectedType>(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<StartingWithConstraint, ExpressionItemType> > StartingWith(std::string expected)
    {
      typedef ExpressionItem<StartingWithConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StartingWithConstraint> Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StartingWithConstraint(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

    ConstraintNode<ExpressionItem<EndingWithConstraint, ExpressionItemType> > EndingWith(std::string expected)
    {
      typedef ExpressionItem<EndingWithConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<EndingWithConstraint> Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new EndingWithConstraint(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

   ConstraintNode<ExpressionItem<OfLengthConstraint, ExpressionItemType> > OfLength(int expected)
    {
      typedef ExpressionItem<OfLengthConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<OfLengthConstraint> Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new OfLengthConstraint(expected)), Base::m_expressionItem));
      ConstraintNode<NextExpressionItemType> node(nextExpressionItem);
      return node;
    }

  };
}

#endif
