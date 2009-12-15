#ifndef _ASSERTIONS_H
#define	_ASSERTIONS_H
#include <stack>
#include "ioperator.h"
#include "logicaloperator.h"
#include "constraint.h"
#include "notoperator.h"
#include "equaltoconstraint.h"
#include "operatorstack.h"
#include "expression.h"
#include "is.h"

class Assert
{
public:

  template <typename T>
  static void That(T actual, Expression& constraint)
  {
    stack<bool> operatorResultsStack;
    stack<string> expectations;

    IOperator* op;
    while ((op = constraint.PopOperator()) != NULL)
    {
      PerformOperation(op, actual, operatorResultsStack, expectations);
    }

    if (!operatorResultsStack.top())
    {
      ostringstream str;
      str << "Expected: ";

      while (!expectations.empty())
      {
        str << expectations.top();
        expectations.pop();

        if(!expectations.empty())
          {
          str << " ";
        }
      }
      str << endl;

      str << "Actual: " << actual << endl;
      throw AssertionException(str.str());
    }
  }

  static void That(bool& actual)
  {
    if (!actual)
    {
      throw AssertionException("Expected condition to be true");
    }
  }

private:

  template <typename T>
  static void PerformOperation(IOperator * op, T actual, stack<bool>& resultStack, stack<string>& expectation)
  {
    expectation.push(op->ExpectationText());

    if (op->IsLogicalOperator())
    {
      LogicalOperator* logical = dynamic_cast<LogicalOperator*> (op);
      logical->Evaluate(resultStack);
    }
    else
    {
      Constraint<T>* constraint = dynamic_cast<Constraint<T>*> (op);
      resultStack.push(constraint->Evaluate(actual));
    }

    delete op;
  }
};

#endif	/* _ASSERTIONS_H */

