#ifndef IGLOO_NODE_H
#define IGLOO_NODE_H

#include "iexpressionowner.h"
#include "nodebase.h"
#include "inodeowner.h"

namespace igloo {

  template <typename T>
    class Node : public NodeBase
  {
  public:
    explicit Node(Expression& expression, INodeOwner<T>& nodeOwner) : NodeBase(expression), m_nodeOwner(nodeOwner) {}

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
