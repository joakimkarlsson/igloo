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

     template <typename T>
    bool Evaluate(T actual)
    {
      return GetExpression().Evaluate(actual);
    }

    std::string ExpressionAsString()
    {
      return GetExpression().ToString();
    }   

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

  template <typename C>
  class ConstraintNode : public Node<C>
  {
  public:
    explicit ConstraintNode(IExpressionOwner& expressionOwner, INodeOwner<C>& nodeOwner) : Node<C>(expressionOwner, nodeOwner) {}

    BinaryNode<C>& And()
    {
      Node<C>::GetExpression().Add(new AndOperator());
      return Node<C>::GetBinaryNode();
    }
  };

  class ConstraintOperations : public Node<ConstraintOperations>
  {
  public:
    explicit ConstraintOperations(IExpressionOwner& expressionOwner, INodeOwner<ConstraintOperations>& nodeOwner) : Node(expressionOwner, nodeOwner) {}

    template <typename T>
    ConstraintNode<ConstraintOperations>& EqualTo(T expected)
    {
      GetExpression().Add(new EqualToConstraint<T>(expected));
      return GetConstraintNode();
    }

    ConstraintNode<ConstraintOperations>& EqualTo(const char* expected)
    {
      return EqualTo<std::string>(std::string(expected));
    }

    template <typename T>
    ConstraintNode<ConstraintOperations>& GreaterThan(T expected)
    {
      GetExpression().Add(new GreaterThanConstraint<T>(expected));
      return GetConstraintNode();
    }

    template <typename T>
      ConstraintNode<ConstraintOperations>& LessThan(T expected)
    {
      GetExpression().Add(new LessThanConstraint<T>(expected));
      return GetConstraintNode();
    }
  };

  class StringConstraintOperations : public Node<StringConstraintOperations>
  {
  public:
    explicit StringConstraintOperations(IExpressionOwner& expressionOwner, INodeOwner<StringConstraintOperations>& nodeOwner) : Node<StringConstraintOperations>(expressionOwner, nodeOwner) {}

    UnaryNode<StringConstraintOperations>& Not()
    {
      GetExpression().Add(new NotOperator());
      return GetUnaryNode();
    }

    ConstraintNode<StringConstraintOperations>& Containing(std::string expectation)
    {
      GetExpression().Add(new StringContainingConstraint(expectation));
      return GetConstraintNode();
    }

    ConstraintNode<StringConstraintOperations>& StartingWith(std::string expectation)
    {
      GetExpression().Add(new StringStartingWithConstraint(expectation));
      return GetConstraintNode();
    }

    ConstraintNode<StringConstraintOperations>& EndingWith(std::string expectation)
    {
      GetExpression().Add(new StringEndingWithConstraint(expectation));
      return GetConstraintNode();
    }

    ConstraintNode<StringConstraintOperations>& OfLength(int expectation)
    {
      GetExpression().Add(new StringOfLengthConstraint(expectation));
      return GetConstraintNode();
    }
  };

  template <typename T>
  class UnaryNode : public T
  {
  public:
    explicit UnaryNode(IExpressionOwner& expressionOwner, INodeOwner<T>& nodeOwner) : T(expressionOwner, nodeOwner) {}
  };

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

  template <typename T>
  class RootNode : public BinaryNode<T>, public IExpressionOwner, public INodeOwner<T>
  {
  public:
    explicit RootNode(std::auto_ptr<Expression> expression) : m_expression(expression), 
      BinaryNode<T>(static_cast<IExpressionOwner&>(*this), static_cast<INodeOwner<T>&>(*this)), 
      m_unaryNode(static_cast<IExpressionOwner&>(*this), static_cast<INodeOwner<T>&>(*this)),
      m_constraintNode(static_cast<IExpressionOwner&>(*this), static_cast<INodeOwner<T>&>(*this))
    {
      
    }

    // IExpressionOwner
    virtual Expression& GetExpression()
    {
      return *(m_expression.get());
    }

    // INodeOwner
    UnaryNode<T>& GetUnaryNode()
    {
      return m_unaryNode;
    }

    BinaryNode<T>& GetBinaryNode()
    {
      return static_cast<BinaryNode<T>&>(*this);
    }

    ConstraintNode<T>& GetConstraintNode()
    {
      return m_constraintNode;
    }

    BinaryNode<StringConstraintOperations>& String()
    {
      m_stringRoot = std::auto_ptr<RootNode<StringConstraintOperations> >(new RootNode<StringConstraintOperations>(m_expression));
      return *(m_stringRoot.get());
    }

  private:
    std::auto_ptr<Expression> m_expression;
    UnaryNode<T> m_unaryNode;
    ConstraintNode<T> m_constraintNode;
    std::auto_ptr<RootNode<StringConstraintOperations> > m_stringRoot;
  };

}

#endif
