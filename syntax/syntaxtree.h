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
  };

  class ConstraintOperations : public Node
  {
  public:
    explicit ConstraintOperations(IExpressionOwner& expressionOwner) : Node(expressionOwner), m_constraintNode(expressionOwner) {}

  private:
    ConstraintNode m_constraintNode;
  };

  class RootNode : public ConstraintOperations, public IExpressionOwner
  {
  public:
    explicit RootNode(std::auto_ptr<Expression> expression) : m_expression(expression), ConstraintOperations(static_cast<IExpressionOwner&>(*this)) 
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
