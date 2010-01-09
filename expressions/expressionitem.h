#ifndef IGLOO_EXPRESSIONITEM_H
#define IGLOO_EXPRESSIONITEM_H

#include "operators/operator.h"
#include "constraints/constraint.h"

namespace igloo {

  class NoopConstraint
  {
  public:
    template <typename ActualType>
      bool Evaluate(ActualType) { return true; }

    void ToString(std::string&) {}
  };

  class NoopExpressionItem
  {
  public:
    typedef NoopConstraint CurrentConstraintType;

    typedef std::stack<bool> ResultStack;
    typedef std::stack<const Operator*> OperatorStack;

    template <typename ActualType>
      void Evaluate(ActualType, ResultStack&, OperatorStack&)
    {
    }

    void ToString(std::string&, bool) {}
  };
  
  template <typename ConstraintType, typename PreviousExpressionItemType>
  class ExpressionItem
  {
  public:
    typedef ConstraintType CurrentConstraintType;

    typedef boost::shared_ptr<Operator> Operator_ptr;
    typedef boost::shared_ptr<ConstraintType> Constraint_ptr;
    typedef boost::shared_ptr<PreviousExpressionItemType> Previous_ptr;
    typedef std::stack<bool> ResultStack;
    typedef std::stack<const Operator*> OperatorStack;

    ExpressionItem() :  m_operator(), m_constraint(), m_previous() {}
    explicit ExpressionItem(Operator_ptr op, Previous_ptr previous) : m_operator(op), m_constraint(), m_previous(previous) {}
    explicit ExpressionItem(Constraint_ptr constraint, Previous_ptr previous) : m_operator(), m_constraint(constraint), m_previous(previous) {}

    template <typename ActualType>
      bool Evaluate(ActualType actual)
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

      if(m_operator.get() != NULL)
      {
        m_operator->ToString(str);
      }

      if(m_constraint.get() != NULL)
      {
        m_constraint->ToString(str);
      }

      if(!last)
      {
        str += " ";
      }
    }

    template <typename ActualType>
      void Evaluate(ActualType actual, ResultStack& resultStack, OperatorStack& operatorStack)
    {
      if(m_previous.get() != NULL)
      {
        m_previous->Evaluate(actual, resultStack, operatorStack);
      }

      if(m_operator.get() != NULL)
      {
        m_operator->Evaluate(operatorStack, resultStack);
      }

      if(m_constraint.get() != NULL)
      {
        resultStack.push(m_constraint->Evaluate(actual));
      }
    }

  private:
    Operator_ptr m_operator;
    Constraint_ptr m_constraint;
    Previous_ptr m_previous;
  };

}

#endif
