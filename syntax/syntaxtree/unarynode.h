#ifndef IGLOO_UNARYNODE_H
#define IGLOO_UNARYNODE_H

#include "iexpressionowner.h"

namespace igloo {

  template <typename T>
  class UnaryNode : public T
  {
  public:
    explicit UnaryNode(Expression& expression, INodeOwner<T>& nodeOwner) : T(expression, nodeOwner) {}
  };

}

#endif
