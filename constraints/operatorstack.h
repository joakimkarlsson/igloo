/* 
 * File:   OperatorStack.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:14 AM
 */

#ifndef _OPERATORSTACK_H
#define	_OPERATORSTACK_H

class OperatorStack
{
public:

  void Push(IOperator* op)
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

#endif

