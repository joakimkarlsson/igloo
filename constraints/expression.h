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

    Expression& Not()
    {
      operators.push_back(new NotOperator());
      return *this;
    }

    Expression& And()
    {
      operators.push_back(new AndOperator());
      return *this;
    }

    template <typename T>
    Expression& EqualTo(T expectation)
    {
      operators.push_back(new EqualToConstraint<T > (expectation));
      return *this;
    }

    Expression& EqualTo(const char* expectation)
    {
      return EqualTo<std::string > (std::string(expectation));
    }

    template <typename T>
    Expression& GreaterThan(T expectation)
    {
      operators.push_back(new GreaterThanConstraint<T > (expectation));
      return *this;
    }

    template <typename T>
    Expression& LessThan(T expectation)
    {
      operators.push_back(new LessThanConstraint<T > (expectation));
      return *this;
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
          if (!operatorStack.empty())
          {
            operatorStack.top()->Evaluate(result);
            operatorStack.pop();
          }

          const LogicalOperator* logical = dynamic_cast<const LogicalOperator*> (op);
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

