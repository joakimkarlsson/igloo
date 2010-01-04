#ifndef IGLOO_STRINGCONSTRAINTOPERATIONS_H
#define IGLOO_STRINGCONSTRAINTOPERATIONS_H

#include "syntaxtree/iexpressionowner.h"

namespace igloo {

  class StringConstraintOperations : public Node<StringConstraintOperations>
  {
  public:
    explicit StringConstraintOperations(Expression& expression, INodeOwner<StringConstraintOperations>& nodeOwner) : Node<StringConstraintOperations>(expression, nodeOwner) {}

    UnaryNode<StringConstraintOperations>& Not()
    {
      GetExpression().Add(new NotOperator());
      return GetUnaryNode();
    }

    ConstraintNode<StringConstraintOperations>& Containing(std::string expectation)
    {
      GetExpression().Add(new StringContainingConstraint(expectation));
      return GetConstraintNode();
    }

    ConstraintNode<StringConstraintOperations>& StartingWith(std::string expectation)
    {
      GetExpression().Add(new StringStartingWithConstraint(expectation));
      return GetConstraintNode();
    }

    ConstraintNode<StringConstraintOperations>& EndingWith(std::string expectation)
    {
      GetExpression().Add(new StringEndingWithConstraint(expectation));
      return GetConstraintNode();
    }

    ConstraintNode<StringConstraintOperations>& OfLength(int expectation)
    {
      GetExpression().Add(new StringOfLengthConstraint(expectation));
      return GetConstraintNode();
    }
  };
}

#endif
