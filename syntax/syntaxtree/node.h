#ifndef IGLOO_NODE_H
#define IGLOO_NODE_H

#include "inodeowner.h"

namespace igloo {

  template <typename ExpressionItemType>
    class Node
  {
  public:
    explicit Node(std::auto_ptr<ExpressionItemType> expressionItem) : m_expressionItem(expressionItem) {}
    Node(const Node<ExpressionItemType>& rhs) : m_expressionItem(rhs.m_expressionItem) {}


  protected:
    mutable std::auto_ptr<ExpressionItemType> m_expressionItem;
  };

}

#endif
