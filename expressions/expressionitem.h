#ifndef IGLOO_EXPRESSIONITEM_H
#define IGLOO_EXPRESSIONITEM_H

#include "operators/operator.h"
#include "constraints/constraint.h"

namespace igloo {

  class RootExpressionItem
  {
  public:
    typedef std::stack<bool> ResultStack;
    typedef std::stack<const Operator*> OperatorStack;

    template <typename ActualType>
      void Evaluate(ActualType, ResultStack&, OperatorStack&)
    {
    }
  };
  
  template <typename CurrentOperandType, typename PreviousExpressionItemType>
  class ExpressionItem
  {
  public:
    typedef std::auto_ptr<Operator> Operator_ptr;
    typedef std::auto_ptr<Constraint<CurrentOperandType> > Constraint_ptr;
    typedef std::auto_ptr<PreviousExpressionItemType> Previous_ptr;
    typedef std::stack<bool> ResultStack;
    typedef std::stack<const Operator*> OperatorStack;

    explicit ExpressionItem(Operator_ptr op, Previous_ptr previous) : m_operator(op), m_constraint(NULL), m_previous(previous) {}
    explicit ExpressionItem(Constraint_ptr constraint, Previous_ptr previous) : m_operator(NULL), m_constraint(constraint), m_previous(previous) {}

    template <typename ActualType>
      bool Evaluate(ActualType actual)
    {
      ResultStack resultStack;
      OperatorStack operatorStack;

      Evaluate(actual, resultStack, operatorStack);

      return resultStack.top();
    }

    template <typename ActualType>
      void Evaluate(ActualType actual, ResultStack& resultStack, OperatorStack& operatorStack)
    {
      if(m_previous.get() == NULL)
      {
        return;
      }

      m_previous->Evaluate(actual, resultStack, operatorStack);

      if(m_operator.get() != NULL)
      {
        if(m_operator->IsLeftAssociative())
        {
          while(!operatorStack.empty())
          {
            operatorStack.top()->Evaluate(resultStack);
            operatorStack.pop();
          }
        }

        operatorStack.push(m_operator.get());
      }

      if(m_constraint.get() != NULL)
      {
        resultStack.push(m_constraint->Evaluate(actual));
      }
    }

  private:
    Previous_ptr m_previous;
    Operator_ptr m_operator;
    Constraint_ptr m_constraint;
  };

}

#endif
