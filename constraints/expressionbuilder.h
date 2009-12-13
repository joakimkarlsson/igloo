/* 
 * File:   expressionbuilder.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:14 AM
 */

#ifndef _EXPRESSIONBUILDER_H
#define	_EXPRESSIONBUILDER_H

class ExpressionBuilder
{
public:

  void Append(IOperator* op)
  {
    _operators.push(op);
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

#endif	/* _EXPRESSIONBUILDER_H */

