#ifndef IGLOO_UNARYNODE_H
#define IGLOO_UNARYNODE_H

#include "iexpressionowner.h"

namespace igloo {

  template <typename OperationsType, typename ExpressionItemType>
  class UnaryNode : public OperationsType
  {
  public:
    explicit UnaryNode(std::auto_ptr<ExpressionItemType> expressionItem) : OperationsType(expressionItem) {}
  };

}

#endif
