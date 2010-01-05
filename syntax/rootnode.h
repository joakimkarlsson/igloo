#ifndef IGLOO_ROOTNODE_H
#define IGLOO_ROOTNODE_H


#include "syntaxtree/binarynode.h"
#include "syntaxtree/unarynode.h"
#include "syntaxtree/constraintnode.h"

namespace igloo {

  class RootNode : public BinaryNode<DummyRootExpressionItem>
  {
  public:
    explicit RootNode() : BinaryNode<DummyRootExpressionItem>(std::auto_ptr<DummyRootExpressionItem>(new DummyRootExpressionItem())) {}
    RootNode(const RootNode& rhs) : BinaryNode<DummyRootExpressionItem>(rhs) {}
  };

}

#endif
