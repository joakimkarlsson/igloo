#ifndef IGLOO_UNARYNODE_H
#define IGLOO_UNARYNODE_H

#include "iexpressionowner.h"

namespace igloo {

  template <typename ExpressionItemType>
  class UnaryNode : public ConstraintOperations<ExpressionItemType>
  {
  public:
    explicit UnaryNode(std::auto_ptr<ExpressionItemType> expressionItem) : ConstraintOperations<ExpressionItemType>(expressionItem) {}
  };

}

#endif
