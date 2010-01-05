#ifndef IGLOO_NODE_H
#define IGLOO_NODE_H

#include "iexpressionowner.h"
#include "nodebase.h"
#include "inodeowner.h"

namespace igloo {

  template <typename ExpressionItemType>
    class Node
  {
  public:
    explicit Node(std::auto_ptr<ExpressionItemType> expressionItem) : m_expressionItem(expressionItem) {}

  protected:
    std::auto_ptr<ExpressionItemType> m_expressionItem;
  };

}

#endif
