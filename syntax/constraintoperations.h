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

    explicit ConstraintOperations(boost::shared_ptr<ExpressionItemType> expressionItem) : Base(expressionItem) {}

    template <typename ExpectedType>
      ConstraintNode<ExpressionItem<EqualToConstraint<ExpectedType>, ExpressionItemType> > EqualTo(ExpectedType expected)
    {
      typedef EqualToConstraint<ExpectedType> ConstraintType;
      return CreateNode(new ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<EqualToConstraint<std::string>, ExpressionItemType> > EqualTo(const char* expected)
    {
      typedef EqualToConstraint<std::string> ConstraintType;
      return CreateNode(new ConstraintType(expected));
    }

    template <typename ExpectedType>
    ConstraintNode<ExpressionItem<GreaterThanConstraint<ExpectedType>, ExpressionItemType> > GreaterThan(ExpectedType expected)
    {
      typedef GreaterThanConstraint<ExpectedType> ConstraintType;
      return CreateNode(new ConstraintType(expected));
    }

    template <typename ExpectedType>
      ConstraintNode<ExpressionItem<LessThanConstraint<ExpectedType>, ExpressionItemType> > LessThan(ExpectedType expected)
    {
      typedef LessThanConstraint<ExpectedType> ConstraintType;
      return CreateNode(new ConstraintType(expected));
    }

    template <typename ExpectedType>
    ConstraintNode<ExpressionItem<ContainingConstraint<ExpectedType>, ExpressionItemType> > Containing(ExpectedType expected)
    {
      typedef ContainingConstraint<ExpectedType> ConstraintType;
      return CreateNode(new ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<StartingWithConstraint, ExpressionItemType> > StartingWith(std::string expected)
    {
      typedef StartingWithConstraint ConstraintType;
      return CreateNode(new ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<EndingWithConstraint, ExpressionItemType> > EndingWith(std::string expected)
    {
      typedef EndingWithConstraint ConstraintType;
      return CreateNode(new ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<OfLengthConstraint, ExpressionItemType> > OfLength(unsigned int expected)
    {
      typedef OfLengthConstraint ConstraintType;
      return CreateNode(new ConstraintType(expected));
    }

  private:
    template <typename ConstraintType>
      ConstraintNode<ExpressionItem<ConstraintType, ExpressionItemType> > CreateNode(ConstraintType* constraint)
    {
      typedef ExpressionItem<ConstraintType, ExpressionItemType> NewExpressionItemType;
      boost::shared_ptr<NewExpressionItemType> expressionItem(new NewExpressionItemType(boost::shared_ptr<ConstraintType>(constraint), Base::m_expressionItem));
      ConstraintNode<NewExpressionItemType> node(expressionItem);
      return node;
    }

  };
}

#endif
