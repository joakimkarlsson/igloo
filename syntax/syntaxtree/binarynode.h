#ifndef IGLOO_BINARYNODE_H
#define IGLOO_BINARYNODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class BinaryNode : public ConstraintOperations<ExpressionItemType>
  {
    typedef ExpressionItem< typename ExpressionItemType::CurrentConstraintType, ExpressionItemType> NextExpressionItemType;
 
  public:
    explicit BinaryNode(boost::shared_ptr<ExpressionItemType> expressionItem) : ConstraintOperations<ExpressionItemType>(expressionItem) {}

    UnaryNode<NextExpressionItemType> Not()
    {
      boost::shared_ptr<NextExpressionItemType> expressionItem( new NextExpressionItemType(boost::shared_ptr<Operator>(new NotOperator()), ConstraintOperations<ExpressionItemType>::m_expressionItem));
      UnaryNode<NextExpressionItemType> node(expressionItem);
      return node;
    }
  };

}

#endif
