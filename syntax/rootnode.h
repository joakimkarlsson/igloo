#ifndef IGLOO_ROOTNODE_H
#define IGLOO_ROOTNODE_H

#include "syntaxtree.h"
#include "stringconstraintoperations.h"
#include "binarynode.h"

namespace igloo {

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
