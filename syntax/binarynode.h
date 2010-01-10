#ifndef IGLOO_BINARYNODE_H
#define IGLOO_BINARYNODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class BinaryNode : public ConstraintOperations<ExpressionItemType>
  {
    typedef ConstraintOperations<ExpressionItemType> Base;
    typedef ExpressionItem<Operator, ExpressionItemType> NextExpressionItemType;
 
  public:
    explicit BinaryNode(boost::shared_ptr<ExpressionItemType> expressionItem) : Base(expressionItem) {}

    UnaryNode<NextExpressionItemType> Not()
    {
      boost::shared_ptr<Operator> op(new NotOperator());
      boost::shared_ptr<NextExpressionItemType> expressionItem( new NextExpressionItemType(op, Base::m_expressionItem));
      return UnaryNode<NextExpressionItemType>(expressionItem);
    }
  };

}

#endif
