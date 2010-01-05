#ifndef IGLOO_CONSTRAINTNODE_H
#define IGLOO_CONSTRAINTNODE_H

#include "iexpressionowner.h"
#include "completestatement.h"

namespace igloo {

  template <typename OperationsType, typename ExpressionItemType>
    class ConstraintNode : public OperationsType
  {
  public:
    explicit ConstraintNode(std::auto_ptr<ExpressionItemType> expressionItem) : OperationsType(expressionItem) {}

    BinaryNode<OperationsType, ExpressionItemType> And()
    {
      ExpressionItemType expressionItem(std::auto_ptr<Operator>(new AndOperator()), OperationsType::m_expressionItem);
      return BinaryNode<OperationsType, ExpressionItemType>(expressionItem);
    }


    template <typename ActualType>
      bool Evaluate(ActualType actual)
    {
      return OperationsType::m_expressionItem->Evaluate(actual);
    }
  };

}

#endif
