#ifndef IGLOO_SYNTAXTREE_H
#define IGLOO_SYNTAXTREE_H


namespace igloo {


  class IExpressionOwner
  {
  public:
    virtual Expression& GetExpression() = 0;
  };

  template <typename T>
  class UnaryNode;

  template <typename T>
  class BinaryNode;

  template <typename T>
  class ConstraintNode;

  template <typename T>
  class INodeOwner
  {
  public:
    virtual UnaryNode<T>& GetUnaryNode() = 0;
    virtual BinaryNode<T>& GetBinaryNode() = 0;
    virtual ConstraintNode<T>& GetConstraintNode() = 0;
  };

  class NodeBase
  {
  public:
    NodeBase(IExpressionOwner& expressionOwner) : m_expressionOwner(expressionOwner) {}  

  protected:
    Expression& GetExpression()
    {
      return m_expressionOwner.GetExpression();
    }

  private:
    IExpressionOwner& m_expressionOwner;    
  };

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
