#ifndef IGLOO_SYNTAXTREE_H
#define IGLOO_SYNTAXTREE_H


namespace igloo {


  class IExpressionOwner
  {
  public:
    virtual Expression& GetExpression() = 0;
  };

  class UnaryNode;
  class BinaryNode;
  class ConstraintNode;

  class INodeOwner
  {
  public:
    virtual UnaryNode& GetUnaryNode() = 0;
    virtual BinaryNode& GetBinaryNode() = 0;
    virtual ConstraintNode& GetConstraintNode() = 0;
  };

  class Node
  {
  public:
    explicit Node(IExpressionOwner& expressionOwner, INodeOwner& nodeOwner) : m_expressionOwner(expressionOwner), m_nodeOwner(nodeOwner) {}

  protected:
    Expression& GetExpression()
    {
      return m_expressionOwner.GetExpression();
    }

    UnaryNode& GetUnaryNode()
    {
      return m_nodeOwner.GetUnaryNode();
    }

    BinaryNode& GetBinaryNode()
    {
      return m_nodeOwner.GetBinaryNode();
    }

    ConstraintNode& GetConstraintNode()
    {
      return m_nodeOwner.GetConstraintNode();
    }

  private:
    IExpressionOwner& m_expressionOwner;
    INodeOwner& m_nodeOwner;
  };

  class ConstraintNode : public Node
  {
  public:
    explicit ConstraintNode(IExpressionOwner& expressionOwner, INodeOwner& nodeOwner) : Node(expressionOwner, nodeOwner) {}

    BinaryNode& And()
    {
      GetExpression().Add(new AndOperator());
      return GetBinaryNode();
    }

    template <typename T>
    bool Evaluate(T actual)
    {
      return GetExpression().Evaluate(actual);
    }

    std::string ExpressionAsString()
    {
      return GetExpression().ToString();
    }
  };

  class ConstraintOperations : public Node
  {
  public:
    explicit ConstraintOperations(IExpressionOwner& expressionOwner, INodeOwner& nodeOwner) : Node(expressionOwner, nodeOwner) {}

    template <typename T>
    ConstraintNode& EqualTo(T expected)
    {
      GetExpression().Add(new EqualToConstraint<T>(expected));
      return GetConstraintNode();
    }

    ConstraintNode& EqualTo(const char* expected)
    {
      return EqualTo<std::string>(std::string(expected));
    }

    template <typename T>
    ConstraintNode& GreaterThan(T expected)
    {
      GetExpression().Add(new GreaterThanConstraint<T>(expected));
      return GetConstraintNode();
    }

    template <typename T>
      ConstraintNode& LessThan(T expected)
    {
      GetExpression().Add(new LessThanConstraint<T>(expected));
      return GetConstraintNode();
    }

  };

  class UnaryNode : public ConstraintOperations
  {
  public:
    explicit UnaryNode(IExpressionOwner& expressionOwner, INodeOwner& nodeOwner) : ConstraintOperations(expressionOwner, nodeOwner) {}
  };

  class BinaryNode : public ConstraintOperations
  {
  public:
    explicit BinaryNode(IExpressionOwner& expressionOwner, INodeOwner& nodeOwner) : ConstraintOperations(expressionOwner, nodeOwner) {}

    UnaryNode& Not()
    {
      GetExpression().Add(new NotOperator());
      return GetUnaryNode();
    }
  };

  class RootNode : public BinaryNode, public IExpressionOwner, public INodeOwner
  {
  public:
    explicit RootNode(std::auto_ptr<Expression> expression) : m_expression(expression), BinaryNode(static_cast<IExpressionOwner&>(*this), static_cast<INodeOwner&>(*this)), m_unaryNode(static_cast<IExpressionOwner&>(*this), static_cast<INodeOwner&>(*this)), m_constraintNode(static_cast<IExpressionOwner&>(*this), static_cast<INodeOwner&>(*this))
    {
      
    }

    // IExpressionOwner
    virtual Expression& GetExpression()
    {
      return *(m_expression.get());
    }

    // INodeOwner
    UnaryNode& GetUnaryNode()
    {
      return m_unaryNode;
    }

    BinaryNode& GetBinaryNode()
    {
      return static_cast<BinaryNode&>(*this);
    }

    ConstraintNode& GetConstraintNode()
    {
      return m_constraintNode;
    }

  private:
    std::auto_ptr<Expression> m_expression;
    UnaryNode m_unaryNode;
    ConstraintNode m_constraintNode;
  };

}

#endif
