#ifndef IGLOO_BINARYNODE_H
#define IGLOO_BINARYNODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class BinaryNode : public ConstraintOperations<ExpressionItemType>
  {
    typedef ConstraintOperations<ExpressionItemType> Base;
    typedef ExpressionItem<NotOperator, ExpressionItemType> NextExpressionItemType;
 
  public:
    explicit BinaryNode(const ExpressionItemType& expressionItem) : Base(expressionItem) {}

    UnaryNode<NextExpressionItemType> Not()
    {
      return UnaryNode<NextExpressionItemType>(NextExpressionItemType(NotOperator(), Base::m_expressionItem));
    }
  };

}

#endif
