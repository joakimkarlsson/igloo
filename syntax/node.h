#ifndef IGLOO_NODE_H
#define IGLOO_NODE_H

#include "syntaxtree.h"

namespace igloo {

  template <typename T>
    class Node : public NodeBase
  {
  public:
    explicit Node(IExpressionOwner& expressionOwner, INodeOwner<T>& nodeOwner) : NodeBase(expressionOwner), m_nodeOwner(nodeOwner) {}

  protected:
    UnaryNode<T>& GetUnaryNode()
    {
      return m_nodeOwner.GetUnaryNode();
    }

    BinaryNode<T>& GetBinaryNode()
    {
      return m_nodeOwner.GetBinaryNode();
    }

    ConstraintNode<T>& GetConstraintNode()
    {
      return m_nodeOwner.GetConstraintNode();
    }

  private:
    INodeOwner<T>& m_nodeOwner;
  };

}

#endif
