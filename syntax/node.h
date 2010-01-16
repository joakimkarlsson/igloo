#ifndef IGLOO_NODE_H
#define IGLOO_NODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class Node
  {
  public:
    explicit Node(const ExpressionItemType& expressionItem) : m_expressionItem(expressionItem) {}
    Node(const Node<ExpressionItemType>& rhs) : m_expressionItem(rhs.m_expressionItem) {}


  protected:
    ExpressionItemType m_expressionItem;
  };

}

#endif
