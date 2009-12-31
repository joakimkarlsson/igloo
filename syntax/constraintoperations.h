#ifndef IGLOO_CONSTRAINTOPERATIONS_H
#define IGLOO_CONSTRAINTOPERATIONS_H

#include "syntaxtree/iexpressionowner.h"
#include "syntaxtree/node.h"

namespace igloo {

  class ConstraintOperations : public Node<ConstraintOperations>
  {
  public:
    explicit ConstraintOperations(IExpressionOwner& expressionOwner, INodeOwner<ConstraintOperations>& nodeOwner) : Node(expressionOwner, nodeOwner) {}

    template <typename T>
    ConstraintNode<ConstraintOperations>& EqualTo(T expected)
    {
      GetExpression().Add(new EqualToConstraint<T>(expected));
      return GetConstraintNode();
    }

    ConstraintNode<ConstraintOperations>& EqualTo(const char* expected)
    {
      return EqualTo<std::string>(std::string(expected));
    }

    template <typename T>
    ConstraintNode<ConstraintOperations>& GreaterThan(T expected)
    {
      GetExpression().Add(new GreaterThanConstraint<T>(expected));
      return GetConstraintNode();
    }

    template <typename T>
      ConstraintNode<ConstraintOperations>& LessThan(T expected)
    {
      GetExpression().Add(new LessThanConstraint<T>(expected));
      return GetConstraintNode();
    }
  };

}

#endif
