#ifndef IGLOO_ROOTNODE_H
#define IGLOO_ROOTNODE_H


#include "binarynode.h"
#include "unarynode.h"
#include "constraintnode.h"

namespace igloo {

  class RootNode : public BinaryNode<NoopExpressionItem>
  {
  public:
    explicit RootNode() : BinaryNode<NoopExpressionItem>(NoopExpressionItem()) {}
  };

}

#endif
