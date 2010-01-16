#ifndef IGLOO_EXPRESSIONITEM_H
#define IGLOO_EXPRESSIONITEM_H

#include "operators/operator.h"
#include "constraints/constraint.h"

namespace igloo {
       
  typedef std::stack<bool> ResultStack;
  typedef std::stack<const Operator*> OperatorStack;

  template <typename ExpressionType, typename ExpressionItemType>
    struct expression_evaluation_trait
  {
    template <typename ActualType>
    static void Evaluate(const ExpressionType& expression, const ActualType& actual, ResultStack& resultStack, OperatorStack&)
    {
      resultStack.push(expression.Evaluate(actual));
    }
  };

  template <typename ExpressionItemType>
    struct expression_evaluation_trait<NotOperator, ExpressionItemType>
  {
    template <typename ActualType>
    static void Evaluate(const Operator& expression, const ActualType&, ResultStack& resultStack, OperatorStack& operatorStack)
    {
      expression.Evaluate(operatorStack, resultStack);
    }
  };     
 
  template <typename ExpressionItemType>
    struct expression_evaluation_trait<OrOperator, ExpressionItemType>
  {
    template <typename ActualType>
    static void Evaluate(const Operator& expression, const ActualType&, ResultStack& resultStack, OperatorStack& operatorStack)
    {
      expression.Evaluate(operatorStack, resultStack);
    }
  };

  template <typename ExpressionItemType>
    struct expression_evaluation_trait<AndOperator, ExpressionItemType>
  {
    template <typename ActualType>
    static void Evaluate(const Operator& expression, const ActualType&, ResultStack& resultStack, OperatorStack& operatorStack)
    {
      expression.Evaluate(operatorStack, resultStack);
    }
  };

  class NoopConstraint
  {
  public:
    template <typename ActualType>
      bool Evaluate(const ActualType&) const { return true; }

    void ToString(std::string&) const {}
  };

  class NoopExpressionItem
  {
  public:
    typedef NoopConstraint CurrentConstraintType;

    template <typename ActualType>
      void Evaluate(const ActualType&, ResultStack&, OperatorStack&) const
    {
    }

    void ToString(std::string&, bool) const {}
  };
  
  template <typename ExpressionType, typename PreviousExpressionItemType>
  class ExpressionItem
  {
  public:
    typedef ExpressionItem<ExpressionType, PreviousExpressionItemType> MyType;

    ExpressionItem(const MyType& rhs) : m_expression(rhs.m_expression), m_previous(rhs.m_previous) {}
    explicit ExpressionItem(const ExpressionType& expression, const PreviousExpressionItemType& previous) : m_expression(expression), m_previous(previous) {}

    template <typename ActualType>
      bool Evaluate(const ActualType& actual) const
    {
      ResultStack resultStack;
      OperatorStack operatorStack;

      Evaluate(actual, resultStack, operatorStack);
      Operator::EvaluateOperatorsOnStack(operatorStack, resultStack);

      return resultStack.top();
    }

    void ToString(std::string& str, bool last = true) const
    {
      m_previous.ToString(str, false);
      m_expression.ToString(str);

      if(!last)
      {
        str += " ";
      }
    }

    template <typename ActualType>
      void Evaluate(const ActualType& actual, ResultStack& resultStack, OperatorStack& operatorStack) const
    {
      m_previous.Evaluate(actual, resultStack, operatorStack);
      expression_evaluation_trait<ExpressionType, MyType>::Evaluate(m_expression, actual, resultStack, operatorStack);
    }

  public:
    ExpressionType m_expression;
    PreviousExpressionItemType m_previous;
  };

}

#endif
