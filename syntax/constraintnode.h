#ifndef IGLOO_CONSTRAINTNODE_H
#define IGLOO_CONSTRAINTNODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class ConstraintNode : public Node<ExpressionItemType>
  {
    typedef Node<ExpressionItemType> Base;
    typedef ExpressionItem<Operator, ExpressionItemType> NextExpressionItemType;
    
  public:
    explicit ConstraintNode(boost::shared_ptr<ExpressionItemType> expressionItem) : Base(expressionItem) {}
    ConstraintNode(const ConstraintNode<ExpressionItemType>& rhs) : Base(rhs) {}

    BinaryNode<NextExpressionItemType> And()
    {
      return CreateNode(new AndOperator());
    }

    BinaryNode<NextExpressionItemType> Or()
    {
      return CreateNode(new OrOperator());
    }

    template <typename ActualType>
      bool Evaluate(const ActualType& actual) const
    {
      return Base::m_expressionItem->Evaluate(actual);
    }

    void ToString(std::string& str) const
    {
      return Base::m_expressionItem->ToString(str);
    }

  private:
    template <typename OperatorType>
    BinaryNode<NextExpressionItemType> CreateNode(OperatorType* op)
    {
      boost::shared_ptr<Operator> op_ptr(op);
      boost::shared_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(op_ptr, Base::m_expressionItem));
      return BinaryNode<NextExpressionItemType>(expressionItem);
    }
  };

}

#endif
