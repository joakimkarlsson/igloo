/* 
 * File:   is.h
 * Author: joakim
 *
 * Created on December 9, 2009, 10:28 AM
 */

#ifndef _IS_H
#define	_IS_H

#include <stack>

class Operator
{
public:
  virtual bool Evaluate(int actual) = 0;

  void SetNextOperator(Operator* op)
  {
    _nextOperator = op;
  }
  
protected:
  Operator* _nextOperator;
};

class NotOperator : public Operator
{
public:

  bool Evaluate(int actual)
  {
    return !_nextOperator->Evaluate(actual);
  }
};

class EqualToOperator : public Operator
{
public:

  EqualToOperator(int expected) : _expected(expected)
  {
  }

  bool Evaluate(int actual)
  {
    return actual == _expected;
  }

private:
  int _expected;
};

class ExpressionBuilder
{
public:

  void Append(Operator* op)
  {
    _operators.push(op);
  }

  Operator* Build()
  {
    Operator* op = 0;

    while (!_operators.empty())
    {
      Operator* popped = _operators.top();
      popped->SetNextOperator(op);
      op = popped;
      _operators.pop();
    }

    return op;
  }

private:
  stack<Operator*> _operators;

};

class ConstraintExpression
{
public:

  ConstraintExpression& Not()
  {
    builder.Append(new NotOperator());
    return *this;
  }

  ConstraintExpression& EqualTo(int expectation)
  {
    builder.Append(new EqualToOperator(expectation));
    return *this;
  }

  bool Assert(int actual)
  {
    Operator* op = builder.Build();
    return op->Evaluate(actual);
  }

private:
  ExpressionBuilder builder;
};

ConstraintExpression Is()
{
  return ConstraintExpression();
}



#endif	/* _IS_H */

