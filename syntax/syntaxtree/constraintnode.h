#ifndef IGLOO_CONSTRAINTNODE_H
#define IGLOO_CONSTRAINTNODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class ConstraintNode : public Node<ExpressionItemType>
  {
    typedef Node<ExpressionItemType> Base;
    typedef ExpressionItem<typename ExpressionItemType::CurrentConstraintType, ExpressionItemType> NextExpressionItemType;
    
  public:
    explicit ConstraintNode(boost::shared_ptr<ExpressionItemType> expressionItem) : Base(expressionItem) {}
    ConstraintNode(const ConstraintNode& rhs) : Base(rhs) {}

    BinaryNode<NextExpressionItemType> And()
    {
      boost::shared_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(boost::shared_ptr<Operator>(new AndOperator()), Base::m_expressionItem));
      BinaryNode<NextExpressionItemType> node(expressionItem);
      return node;
    }

    template <typename ActualType>
      bool Evaluate(ActualType actual) const
    {
      return Base::m_expressionItem->Evaluate(actual);
    }

    void ToString(std::string& str) const
    {
      return Base::m_expressionItem->ToString(str);
    }
  };

}

#endif
