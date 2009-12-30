#ifndef IGLOO_SYNTAXTREE_H
#define IGLOO_SYNTAXTREE_H


namespace igloo {


  class IExpressionOwner
  {
  public:
    virtual Expression& GetExpression() = 0;
  };

  class Node
  {
  public:
    explicit Node(IExpressionOwner& expressionOwner) : m_expressionOwner(expressionOwner) {}

    Expression& GetExpression()
    {
      return m_expressionOwner.GetExpression();
    }

  private:
    IExpressionOwner& m_expressionOwner;
  };

  class ConstraintNode : public Node
  {
  public:
    explicit ConstraintNode(IExpressionOwner& expressionOwner) : Node(expressionOwner) {}

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
    explicit ConstraintOperations(IExpressionOwner& expressionOwner) : Node(expressionOwner), m_constraintNode(expressionOwner) {}

    template <typename T>
    ConstraintNode& EqualTo(T expected)
    {
      GetExpression().Add(new EqualToConstraint<T>(expected));
      return m_constraintNode;
    }

    ConstraintNode& EqualTo(const char* expected)
    {
      return EqualTo<std::string>(std::string(expected));
    }

    template <typename T>
    ConstraintNode& GreaterThan(T expected)
    {
      GetExpression().Add(new GreaterThanConstraint<T>(expected));
      return m_constraintNode;
    }

  private:
    ConstraintNode m_constraintNode;
  };

  class UnaryNode : public ConstraintOperations
  {
  public:
    explicit UnaryNode(IExpressionOwner& expressionOwner) : ConstraintOperations(expressionOwner) {}
  };

  class BinaryNode : public ConstraintOperations
  {
  public:
    explicit BinaryNode(IExpressionOwner& expressionOwner) : ConstraintOperations(expressionOwner), m_unaryNode(expressionOwner) {}

    UnaryNode& Not()
    {
      GetExpression().Add(new NotOperator());
      return m_unaryNode;
    }

  private:
    UnaryNode m_unaryNode;
  };

  class RootNode : public BinaryNode, public IExpressionOwner
  {
  public:
    explicit RootNode(std::auto_ptr<Expression> expression) : m_expression(expression), BinaryNode(static_cast<IExpressionOwner&>(*this)) 
    {
    }

    // IExpressionOwner
    virtual Expression& GetExpression()
    {
      return *(m_expression.get());
    }

  private:
    std::auto_ptr<Expression> m_expression;
  };

}

#endif
