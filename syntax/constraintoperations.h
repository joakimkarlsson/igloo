#ifndef IGLOO_CONSTRAINTOPERATIONS_H
#define IGLOO_CONSTRAINTOPERATIONS_H

#include "node.h"

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

    explicit ConstraintOperations(const ExpressionItemType& expressionItem) : Base(expressionItem) {}

    template <typename ExpectedType>
      ConstraintNode<ExpressionItem<EqualToConstraint<ExpectedType>, ExpressionItemType> > EqualTo(ExpectedType expected)
    {
      typedef EqualToConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<EqualToConstraint<std::string>, ExpressionItemType> > EqualTo(const char* expected)
    {
      typedef EqualToConstraint<std::string> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType>
    ConstraintNode<ExpressionItem<GreaterThanConstraint<ExpectedType>, ExpressionItemType> > GreaterThan(ExpectedType expected)
    {
      typedef GreaterThanConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType>
      ConstraintNode<ExpressionItem<LessThanConstraint<ExpectedType>, ExpressionItemType> > LessThan(ExpectedType expected)
    {
      typedef LessThanConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType>
    ConstraintNode<ExpressionItem<ContainingConstraint<ExpectedType>, ExpressionItemType> > Containing(ExpectedType expected)
    {
      typedef ContainingConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<StartingWithConstraint, ExpressionItemType> > StartingWith(const std::string& expected)
    {
      typedef StartingWithConstraint ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<EndingWithConstraint, ExpressionItemType> > EndingWith(const std::string& expected)
    {
      typedef EndingWithConstraint ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<OfLengthConstraint, ExpressionItemType> > OfLength(unsigned int expected)
    {
      typedef OfLengthConstraint ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

  private:
    template <typename ConstraintType>
      ConstraintNode<ExpressionItem<ConstraintType, ExpressionItemType> > CreateNode(const ConstraintType& constraint)
    {
      typedef ExpressionItem<ConstraintType, ExpressionItemType> NewExpressionItemType;
      ConstraintNode<NewExpressionItemType> node(NewExpressionItemType(constraint, Base::m_expressionItem));
      return node;
    }

  };
}

#endif
