#ifndef IGLOO_CONSTRAINTNODE_H
#define IGLOO_CONSTRAINTNODE_H

#include "iexpressionowner.h"
#include "completestatement.h"

namespace igloo {

  template <typename T>
    class ConstraintNode : public Node<T>, public CompleteStatement
  {
  public:
    explicit ConstraintNode(IExpressionOwner& expressionOwner, INodeOwner<T>& nodeOwner) : Node<T>(expressionOwner, nodeOwner), CompleteStatement(expressionOwner) {}

    BinaryNode<T>& And()
    {
      Node<T>::GetExpression().Add(new AndOperator());
      return Node<T>::GetBinaryNode();
    }
  };

}

#endif
