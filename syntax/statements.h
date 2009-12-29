#ifndef IGLOO_NODES_H_
#define IGLOO_NODES_H_

#include "../expressions.h"

namespace igloo {

  class UnaryNode;
  class GeneralConstraintNode;
  class BinaryNode;
  class StringRootNode;
  class StringConstraintNode;
  class StringUnaryNode;
  class StringBinaryNode;

  class Node;
  class INodeFactory
  {
  public:
    virtual UnaryNode* CreateUnary(Node& previous) = 0;
    virtual BinaryNode* CreateBinary(Node& previous) = 0;
    virtual GeneralConstraintNode* CreateConstraint(Node& previous) = 0;
    virtual StringRootNode* CreateStringRootNode(Node& previous) = 0;
    virtual StringConstraintNode* CreateStringConstraintNode(Node& previous) = 0;
    virtual StringUnaryNode* CreateStringUnaryNode(Node& previous) = 0;
    virtual StringBinaryNode* CreateStringBinaryNode(Node& previous) = 0;
  };

  class Node
  {
  public:
    explicit Node(std::auto_ptr<Expression> expression, std::auto_ptr<INodeFactory> nodeFactory) : m_expression(expression), m_nodeFactory(nodeFactory) {}
    explicit Node(Node& previous) : m_expression(previous.m_expression), m_nodeFactory(previous.m_nodeFactory) {}

    template <typename T>
      bool Evaluate(T actual)
    {
      return m_expression->Evaluate(actual);
    }

    std::string ExpressionAsString()
    {
      return m_expression->ToString();
    }

  protected:
    void AppendExpression(IToken* token)
    {
      m_expression->Add(token);
    }

    GeneralConstraintNode& MoveToGeneralConstraintNode()
    {
      GeneralConstraintNode* node = m_nodeFactory->CreateConstraint(*this);
      return *node;
    }

    UnaryNode& MoveToUnaryNode()
    {
      UnaryNode* node = m_nodeFactory->CreateUnary(*this);
      return *node;
    }

    BinaryNode& MoveToBinaryNode()
    {
      return *(m_nodeFactory->CreateBinary(*this));
    }

    StringRootNode& MoveToStringRootNode()
    {
      return *(m_nodeFactory->CreateStringRootNode(*this));
    }

    StringConstraintNode& MoveToStringConstraintNode()
    {
      return *(m_nodeFactory->CreateStringConstraintNode(*this));
    }

    StringUnaryNode& MoveToStringUnaryNode()
    {
      return *(m_nodeFactory->CreateStringUnaryNode(*this));
    }

    StringBinaryNode& MoveToStringBinaryNode()
    {
      return *(m_nodeFactory->CreateStringBinaryNode(*this));
    }

  private:
    std::auto_ptr<INodeFactory> m_nodeFactory;
    std::auto_ptr<Expression> m_expression;
  };

  class ConstraintNode : public Node
  {
  public:
    explicit ConstraintNode(Node& previous) : Node(previous) {}
  };

  class GeneralConstraintNode : public ConstraintNode
  {
  public:
    explicit GeneralConstraintNode(Node& previous) : ConstraintNode(previous) {}

    BinaryNode& And()
    {
      AppendExpression(new AndOperator());
      return MoveToBinaryNode();
    }
  };

  class StringConstraintNode : public ConstraintNode
  {
  public:
    explicit StringConstraintNode(Node& previous) : ConstraintNode(previous) {}

    StringBinaryNode& And()
    {
      AppendExpression(new AndOperator());
      return MoveToStringBinaryNode();
    };
  };

  class UnaryNode : public Node
  {
  public:
    explicit UnaryNode(Node& previous) : Node(previous) {}

    template <typename T>
      GeneralConstraintNode& EqualTo(T expected)
    {
      AppendExpression(new EqualToConstraint<T>(expected));
      return MoveToGeneralConstraintNode();
    }

    GeneralConstraintNode& EqualTo(const char* expectation)
    {
      return EqualTo<std::string > (std::string(expectation));
    }

    template <typename T>
      GeneralConstraintNode& GreaterThan(T expectation)
    {
      AppendExpression(new GreaterThanConstraint<T > (expectation));
      return MoveToGeneralConstraintNode();
    }

    template <typename T>
      GeneralConstraintNode& LessThan(T expectation)
    {
      AppendExpression(new LessThanConstraint<T > (expectation));
      return MoveToGeneralConstraintNode();
    }
  };

  class StringUnaryNode : public Node
  {
  public:
    explicit StringUnaryNode(Node& previous) : Node(previous) {}

    StringConstraintNode& Containing(std::string expectation)
    {
      AppendExpression(new StringContainingConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& StartingWith(std::string expectation)
    {
      AppendExpression(new StringStartingWithConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& EndingWith(std::string expectation)
    {
      AppendExpression(new StringEndingWithConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& OfLength(int expectation)
    {
      AppendExpression(new StringOfLengthConstraint(expectation));
      return MoveToStringConstraintNode();
    }
  };

    class StringBinaryNode : public Node
    {
    public:
      explicit StringBinaryNode(Node& previous) : Node(previous) {}

    StringUnaryNode& Not()
    {
      AppendExpression(new NotOperator());
      return MoveToStringUnaryNode();
    }

     StringConstraintNode& Containing(std::string expectation)
    {
      AppendExpression(new StringContainingConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& StartingWith(std::string expectation)
    {
      AppendExpression(new StringStartingWithConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& EndingWith(std::string expectation)
    {
      AppendExpression(new StringEndingWithConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& OfLength(int expectation)
    {
      AppendExpression(new StringOfLengthConstraint(expectation));
      return MoveToStringConstraintNode();
    }     
  };    

  class BinaryNode : public Node
  {
  public:
    explicit BinaryNode(Node& previous) : Node(previous) {}
 
    UnaryNode& Not()
    {
      AppendExpression(new NotOperator());
      return MoveToUnaryNode();
    }

    template <typename T>
      GeneralConstraintNode& EqualTo(T expected)
    {
      AppendExpression(new EqualToConstraint<T>(expected));
      return MoveToGeneralConstraintNode();
    }

    GeneralConstraintNode& EqualTo(const char* expectation)
    {
      return EqualTo<std::string > (std::string(expectation));
    }

    template <typename T>
      GeneralConstraintNode& GreaterThan(T expectation)
    {
      AppendExpression(new GreaterThanConstraint<T > (expectation));
      return MoveToGeneralConstraintNode();
    }

    template <typename T>
      GeneralConstraintNode& LessThan(T expectation)
    {
      AppendExpression(new LessThanConstraint<T > (expectation));
      return MoveToGeneralConstraintNode();
    }
  };

  class StringRootNode : public Node
  {
  public:
    explicit StringRootNode(Node& previous) : Node(previous) {}

    StringUnaryNode& Not()
    {
      AppendExpression(new NotOperator());
      return MoveToStringUnaryNode();
    }

    StringConstraintNode& Containing(std::string expectation)
    {
      AppendExpression(new StringContainingConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& StartingWith(std::string expectation)
    {
      AppendExpression(new StringStartingWithConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& EndingWith(std::string expectation)
    {
      AppendExpression(new StringEndingWithConstraint(expectation));
      return MoveToStringConstraintNode();
    }

    StringConstraintNode& OfLength(int expectation)
    {
      AppendExpression(new StringOfLengthConstraint(expectation));
      return MoveToStringConstraintNode();
    }
  };

  class RootNode : public Node
  {
  public:
    explicit RootNode(std::auto_ptr<Expression> expression, std::auto_ptr<INodeFactory> nodeFactory) : Node(expression, nodeFactory) {}

    UnaryNode& Not()
    {
      AppendExpression(new NotOperator());
      return MoveToUnaryNode();
    }

    template <typename T>
    GeneralConstraintNode& EqualTo(T expected)
    {
      AppendExpression(new EqualToConstraint<T>(expected));
      return MoveToGeneralConstraintNode();
    }

    GeneralConstraintNode& EqualTo(const char* expectation)
    {
      return EqualTo<std::string > (std::string(expectation));
    }

    template <typename T>
    GeneralConstraintNode& GreaterThan(T expectation)
    {
      AppendExpression(new GreaterThanConstraint<T > (expectation));
      return MoveToGeneralConstraintNode();
    }

    template <typename T>
    GeneralConstraintNode& LessThan(T expectation)
    {
      AppendExpression(new LessThanConstraint<T > (expectation));
      return MoveToGeneralConstraintNode();
    }

    StringRootNode& String()
    {
      return MoveToStringRootNode();
    }
  };

  class NodeFactory : public INodeFactory
  {
  public:
    virtual ~NodeFactory()
    {
      std::list<Node*>::iterator it;
      for(it = m_createdNodes.begin(); it != m_createdNodes.end(); it++)
      {
        delete (*it);
      }
    }

    virtual UnaryNode* CreateUnary(Node& previous)
    {
      UnaryNode* node = new UnaryNode(previous);
      m_createdNodes.push_back(node);
      return node;
    }

    virtual BinaryNode* CreateBinary(Node& previous)
    {
      BinaryNode* node = new BinaryNode(previous);
      m_createdNodes.push_back(node);
      return node;
    }

    virtual GeneralConstraintNode* CreateConstraint(Node& previous)
    {
      GeneralConstraintNode* node = new GeneralConstraintNode(previous);
      m_createdNodes.push_back(node);
      return node;
    }

    virtual StringRootNode* CreateStringRootNode(Node& previous)
    {
      StringRootNode* node = new StringRootNode(previous);
      m_createdNodes.push_back(node);
      return node;
    }

    virtual StringConstraintNode* CreateStringConstraintNode(Node& previous)
    {
      StringConstraintNode* node = new StringConstraintNode(previous);
      m_createdNodes.push_back(node);
      return node;
    }

    virtual StringUnaryNode* CreateStringUnaryNode(Node& previous)
    {
      StringUnaryNode* node = new StringUnaryNode(previous);
      m_createdNodes.push_back(node);
      return node;
    }

    virtual StringBinaryNode* CreateStringBinaryNode(Node& previous)
    {
      StringBinaryNode* node = new StringBinaryNode(previous);
      m_createdNodes.push_back(node);
      return node;
    }


  private:
    std::list<Node*> m_createdNodes;
  };
}

#endif
