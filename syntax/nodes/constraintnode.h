#ifndef IGLOO_CONSTRAINTNODE_H
#define IGLOO_CONSTRAINTNODE_H

namespace igloo {

  template <typename ExpressionItemType>
    class ConstraintNode : public Node<ExpressionItemType>
  {
    typedef Node<ExpressionItemType> Base;
    
  public:
    explicit ConstraintNode(const ExpressionItemType& expressionItem) : Base(expressionItem) {}
    ConstraintNode(const ConstraintNode<ExpressionItemType>& rhs) : Base(rhs) {}

    BinaryNode<ExpressionItem<AndOperator_OLD, ExpressionItemType> > And()
    {
      return CreateNode<AndOperator_OLD>();
    }

    BinaryNode<ExpressionItem<OrOperator, ExpressionItemType> > Or()
    {
      return CreateNode<OrOperator>();
    }

    template <typename ActualType>
      bool Evaluate(const ActualType& actual) const
    {
      return Base::m_expressionItem.Evaluate<ActualType>(actual);
    }

    void ToString(std::string& str) const
    {
      return Base::m_expressionItem.ToString(str);
    }

  private:
    template <typename OperatorType>
    BinaryNode<ExpressionItem<OperatorType, ExpressionItemType> > CreateNode()
    {
   	  typedef ExpressionItem<OperatorType, ExpressionItemType> NextExpressionItemType;
      return BinaryNode<NextExpressionItemType>(NextExpressionItemType(OperatorType(), Base::m_expressionItem));
    }
  };

}

#endif
