#ifndef IGLOO_BINARYNODE_H
#define IGLOO_BINARYNODE_H

#include "iexpressionowner.h"

namespace igloo {

  template <typename OperationsType, typename ExpressionItemType>
  class BinaryNode : public OperationsType
  {
  public:
    explicit BinaryNode(std::auto_ptr<ExpressionItemType> expressionItem) : OperationsType(expressionItem) {}

    UnaryNode<OperationsType, ExpressionItemType> Not()
    {
      ExpressionItemType expressionItem(std::auto_ptr<Operator>(new NotOperator()), OperationsType::m_expressionItem);
      return UnaryNode<OperationsType, ExpressionItemType>(expressionItem);
    }
  };

}

#endif
