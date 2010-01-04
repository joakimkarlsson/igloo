#ifndef IGLOO_CONSTRAINTNODE_H
#define IGLOO_CONSTRAINTNODE_H

#include "iexpressionowner.h"
#include "completestatement.h"

namespace igloo {

  template <typename T>
    class ConstraintNode : public Node<T>, public CompleteStatement
  {
  public:
    explicit ConstraintNode(Expression& expression, INodeOwner<T>& nodeOwner) : Node<T>(expression, nodeOwner), CompleteStatement(expression) {}

    BinaryNode<T>& And()
    {
      Node<T>::GetExpression().Add(new AndOperator());
      return Node<T>::GetBinaryNode();
    }
  };

}

#endif
