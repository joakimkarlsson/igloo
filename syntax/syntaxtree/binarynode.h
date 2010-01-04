#ifndef IGLOO_BINARYNODE_H
#define IGLOO_BINARYNODE_H

#include "iexpressionowner.h"

namespace igloo {

  template <typename T>
  class BinaryNode : public T
  {
  public:
    explicit BinaryNode(Expression& expression, INodeOwner<T>& nodeOwner) : T(expression, nodeOwner) {}

    UnaryNode<T>& Not()
    {
      T::GetExpression().Add(new NotOperator());
      return T::GetUnaryNode();
    }
  };

}

#endif
