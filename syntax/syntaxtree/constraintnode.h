#ifndef IGLOO_CONSTRAINTNODE_H
#define IGLOO_CONSTRAINTNODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class ConstraintNode : public ConstraintOperations<ExpressionItemType>
  {
    typedef ExpressionItem<typename ExpressionItemType::CurrentConstraintType, ExpressionItemType> NextExpressionItemType;
    
  public:
    explicit ConstraintNode(std::auto_ptr<ExpressionItemType> expressionItem) : ConstraintOperations<ExpressionItemType>(expressionItem) {}
    ConstraintNode(const ConstraintNode<ExpressionItemType>& rhs) : ConstraintOperations<ExpressionItemType>(rhs) {}


    BinaryNode<NextExpressionItemType> And()
    {
      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(std::auto_ptr<Operator>(new AndOperator()), ConstraintOperations<ExpressionItemType>::m_expressionItem));
      return BinaryNode<NextExpressionItemType>(expressionItem);
    }


    template <typename ActualType>
      bool Evaluate(ActualType actual) const
    {
      return ConstraintOperations<ExpressionItemType>::m_expressionItem->Evaluate(actual);
    }

    void ToString(std::string& str) const
    {
      return ConstraintOperations<ExpressionItemType>::m_expressionItem->ToString(str);
    }
  };

}

#endif
