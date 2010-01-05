#ifndef IGLOO_NODE_H
#define IGLOO_NODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class Node
  {
  public:
    explicit Node(std::auto_ptr<ExpressionItemType> expressionItem) : m_expressionItem(expressionItem) {}
    Node(Node& rhs) : m_expressionItem(rhs.m_expressionItem) {}


  protected:
    std::auto_ptr<ExpressionItemType> m_expressionItem;
  };

}

#endif
