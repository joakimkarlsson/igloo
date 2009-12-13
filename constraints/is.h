/* 
 * File:   is.h
 * Author: joakim
 *
 * Created on December 9, 2009, 10:28 AM
 */

#ifndef _IS_H
#define	_IS_H

#include <stack>
#include "ioperator.h"
#include "logicaloperator.h"
#include "constraint.h"
#include "notoperator.h"
#include "equaltooperator.h"

class ExpressionBuilder
{
public:

  void Append(IOperator* op)
  {
    _operators.push(op);
  }

  IOperator* Build()
  {
    IOperator* op = 0;

    while (!_operators.empty())
    {
      IOperator* popped = _operators.top();
      popped->SetNextOperator(op);
      op = popped;
      _operators.pop();
    }

    return op;
  }

  IOperator* Pop()
  {
    if (_operators.empty())
    {
      return NULL;
    }

    IOperator* popped = _operators.top();
    _operators.pop();
    return popped;
  }

private:
  stack<IOperator* > _operators;

};

class ConstraintExpression
{
public:

  ConstraintExpression& Not()
  {
    builder.Append(new NotOperator());
    return *this;
  }

  template <typename T>
  ConstraintExpression& EqualTo(T expectation)
  {
    builder.Append(new EqualToOperator<T > (expectation));
    return *this;
  }

  IOperator* PopOperator()
  {
    return builder.Pop();
  }

private:
  ExpressionBuilder builder;
};

ConstraintExpression Is()
{
  return ConstraintExpression();
}



#endif	/* _IS_H */

