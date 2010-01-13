#ifndef IGLOO_EXPRESSIONITEM_H
#define IGLOO_EXPRESSIONITEM_H

#include "operators/operator.h"
#include "constraints/constraint.h"

namespace igloo {

  template <typename ExpressionType, typename ExpressionItemType>
    struct expression_evaluation_trait
  {
    typedef std::stack<bool> ResultStack;
    typedef std::stack<const Operator*> OperatorStack;

    template <typename ActualType>
    static void Evaluate(const ExpressionType& expression, const ActualType& actual, ResultStack& resultStack, OperatorStack&)
    {
      resultStack.push(expression.Evaluate(actual));
    }
  };

  template <typename ExpressionItemType>
    struct expression_evaluation_trait<Operator, ExpressionItemType>
  {
    typedef std::stack<bool> ResultStack;
    typedef std::stack<const Operator*> OperatorStack;

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
      bool Evaluate(const ActualType&) { return true; }

    void ToString(std::string&) {}
  };

  class NoopExpressionItem
  {
  public:
    typedef NoopConstraint CurrentConstraintType;

    typedef std::stack<bool> ResultStack;
    typedef std::stack<const Operator*> OperatorStack;

    template <typename ActualType>
      void Evaluate(const ActualType&, ResultStack&, OperatorStack&)
    {
    }

    void ToString(std::string&, bool) {}
  };
  
  template <typename ExpressionType, typename PreviousExpressionItemType>
  class ExpressionItem
  {
  public:
    typedef ExpressionItem<ExpressionType, PreviousExpressionItemType> MyType;

    typedef boost::shared_ptr<ExpressionType> Expression_ptr;
    typedef boost::shared_ptr<PreviousExpressionItemType> Previous_ptr;
    typedef std::stack<bool> ResultStack;
    typedef std::stack<const Operator*> OperatorStack;

    ExpressionItem() : m_expression(), m_previous() {}
    explicit ExpressionItem(Expression_ptr expression, Previous_ptr previous) : m_expression(expression), m_previous(previous) {}

    template <typename ActualType>
      bool Evaluate(const ActualType& actual)
    {
      ResultStack resultStack;
      OperatorStack operatorStack;

      Evaluate(actual, resultStack, operatorStack);
      Operator::EvaluateOperatorsOnStack(operatorStack, resultStack);

      return resultStack.top();
    }

    void ToString(std::string& str, bool last = true)
    {
      if(m_previous.get() == NULL)
      {
        return;
      }

      m_previous->ToString(str, false);

      m_expression->ToString(str);

      if(!last)
      {
        str += " ";
      }
    }

    template <typename ActualType>
      void Evaluate(const ActualType& actual, ResultStack& resultStack, OperatorStack& operatorStack)
    {
      if(m_previous.get() != NULL)
      {
        m_previous->Evaluate(actual, resultStack, operatorStack);
      }

      expression_evaluation_trait<ExpressionType, MyType>::Evaluate(*(m_expression.get()), actual, resultStack, operatorStack);
    }

  public:
    Expression_ptr m_expression;
    Previous_ptr m_previous;
  };

}

#endif
