#ifndef IGLOO_BINARYNODE_H
#define IGLOO_BINARYNODE_H

#include "syntaxtree.h"

namespace igloo {

  template <typename T>
  class BinaryNode : public T
  {
  public:
    explicit BinaryNode(IExpressionOwner& expressionOwner, INodeOwner<T>& nodeOwner) : T(expressionOwner, nodeOwner) {}

    UnaryNode<T>& Not()
    {
      T::GetExpression().Add(new NotOperator());
      return T::GetUnaryNode();
    }
  };

}

#endif
