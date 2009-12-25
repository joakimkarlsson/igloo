/* 
 * File:   Expression.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:42 AM
 */

#ifndef _EXPRESSION_H
#define	_EXPRESSION_H

#include "ioperator.h"
#include "logicaloperator.h"


using std::auto_ptr;

namespace igloo {

  class Expression {
  public:
    typedef std::list<IOperator*> Operators;

    void Add(IOperator* op)
    {
      operators.push_back(op);
    }

    template <typename T>
    bool Evaluate(T actual) const
    {
      std::stack<const LogicalOperator*> operatorStack;
      std::stack<bool> result;

      for (Operators::const_iterator it = operators.begin(); it != operators.end(); it++)
      {
        IOperator* op = *it;
        if (op->IsLogicalOperator())
        {
          const LogicalOperator* logical = dynamic_cast<const LogicalOperator*> (op);

          if (logical->IsLeftAssociative())
          {
            while (!operatorStack.empty())
            {
              operatorStack.top()->Evaluate(result);
              operatorStack.pop();
            }
          }

          operatorStack.push(logical);
        }
        else
        {
          const Constraint<T>* constraint = dynamic_cast<const Constraint<T>*> (op);
          result.push(constraint->Evaluate(actual));
        }
      }

      while (!operatorStack.empty())
      {
        operatorStack.top()->Evaluate(result);
        operatorStack.pop();
      }

      return result.top();
    }

    std::string GetExpectationText() const
    {
      std::string expectationText;

      for (Operators::const_iterator it = operators.begin(); it != operators.end();)
      {
        expectationText += (*it)->ExpectationText();

        it++;
        if (it != operators.end())
        {
          expectationText += " ";
        }
      }

      return expectationText;
    }

  private:
    Operators operators;
  };
}
#endif

