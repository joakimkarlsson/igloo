/* 
 * File:   Expression.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:42 AM
 */

#ifndef _EXPRESSION_H
#define	_EXPRESSION_H

#include "itoken.h"
#include "operator.h"


using std::auto_ptr;

namespace igloo {

  class Expression
  {
  public:
    typedef std::list<IToken*> Tokens;

    virtual ~Expression()
    {
      Tokens::iterator it;
      for (it = tokens.begin(); it != tokens.end(); it++)
      {
        delete (*it);
      }
    }

    void Add(IToken* op)
    {
      tokens.push_back(op);
    }

    template <typename T>
    bool Evaluate(T actual) const
    {
      std::stack<const Operator*> operatorStack;
      std::stack<bool> result;

      for (Tokens::const_iterator it = tokens.begin(); it != tokens.end(); it++)
      {
        IToken* op = *it;
        if (op->IsOperator())
        {
          const Operator* logical = dynamic_cast<const Operator*> (op);

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

      for (Tokens::const_iterator it = tokens.begin(); it != tokens.end();)
      {
        expectationText += (*it)->ExpectationText();

        it++;
        if (it != tokens.end())
        {
          expectationText += " ";
        }
      }

      return expectationText;
    }

  private:
    Tokens tokens;
  };
}
#endif

