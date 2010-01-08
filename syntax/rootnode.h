#ifndef IGLOO_ROOTNODE_H
#define IGLOO_ROOTNODE_H


#include "syntaxtree/binarynode.h"
#include "syntaxtree/unarynode.h"
#include "syntaxtree/constraintnode.h"

namespace igloo {

  class RootNode : public BinaryNode<NoopExpressionItem>
  {
  public:
    explicit RootNode() : BinaryNode<NoopExpressionItem>(boost::shared_ptr<NoopExpressionItem>(new NoopExpressionItem())) {}
  };

}

#endif
