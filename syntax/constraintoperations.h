#ifndef IGLOO_CONSTRAINTOPERATIONS_H
#define IGLOO_CONSTRAINTOPERATIONS_H

#include "node.h"   
#include "../constraints/expressions/expression.h"
#include "../constraints/equalsconstraint.h" 
#include "../constraints/endswithconstraint.h"
#include "../constraints/containsconstraint.h"
#include "../constraints/haslengthconstraint.h"
#include "../constraints/isgreaterthanconstraint.h"
#include "../constraints/islessthanconstraint.h"
#include "../constraints/startswithconstraint.h"


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
      ConstraintNode<ExpressionItem<EqualsConstraint<ExpectedType>, ExpressionItemType> > EqualTo(ExpectedType expected)
    {
      typedef EqualsConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    ConstraintNode<ExpressionItem<EqualsConstraint<std::string>, ExpressionItemType> > EqualTo(const char* expected)
    {
      typedef EqualsConstraint<std::string> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType>
    ConstraintNode<ExpressionItem<IsGreaterThanConstraint<ExpectedType>, ExpressionItemType> > GreaterThan(ExpectedType expected)
    {
      typedef IsGreaterThanConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType>
      ConstraintNode<ExpressionItem<IsLessThanConstraint<ExpectedType>, ExpressionItemType> > LessThan(ExpectedType expected)
    {
      typedef IsLessThanConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType>
    ConstraintNode<ExpressionItem<ContainsConstraint<ExpectedType>, ExpressionItemType> > Containing(ExpectedType expected)
    {
      typedef ContainsConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType> 
    ConstraintNode<ExpressionItem<StartsWithConstraint<ExpectedType>, ExpressionItemType> > StartingWith(const std::string& expected)
    {
      typedef StartsWithConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType> 
    ConstraintNode<ExpressionItem<EndsWithConstraint<ExpectedType>, ExpressionItemType> > EndingWith(const std::string& expected)
    {
      typedef EndsWithConstraint<ExpectedType> ConstraintType;
      return CreateNode(ConstraintType(expected));
    }

    template <typename ExpectedType> 
    ConstraintNode<ExpressionItem<HasLengthConstraint<ExpectedType>, ExpressionItemType> > OfLength(unsigned int expected)
    {
      typedef HasLengthConstraint<ExpectedType> ConstraintType;
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
