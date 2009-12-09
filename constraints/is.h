/* 
 * File:   is.h
 * Author: joakim
 *
 * Created on December 9, 2009, 10:28 AM
 */

#ifndef _IS_H
#define	_IS_H

#include <stack>

template <typename T>
class Operator
{
public:
  virtual bool Evaluate(T actual) = 0;

  void SetNextOperator(Operator<T>* op)
  {
    _nextOperator = op;
  }
  
protected:
  Operator<T>* _nextOperator;
};

template <typename T>
class NotOperator : public Operator<T>
{
public:

  virtual bool Evaluate(T actual)
  {
    return !Operator<T>::_nextOperator->Evaluate(actual);
  }
};

template <typename T>
class EqualToOperator : public Operator<T>
{
public:

  EqualToOperator(T expected) : _expected(expected)
  {
  }

  bool Evaluate(T actual)
  {
    return actual == _expected;
  }

private:
  T _expected;
};

template <typename T>
class ExpressionBuilder
{
public:

  void Append(Operator<T>* op)
  {
    _operators.push(op);
  }

  Operator<T>* Build()
  {
    Operator<T>* op = 0;

    while (!_operators.empty())
    {
      Operator<T>* popped = _operators.top();
      popped->SetNextOperator(op);
      op = popped;
      _operators.pop();
    }

    return op;
  }

private:
  stack<Operator<T>* > _operators;

};

template <typename T>
class ConstraintExpression
{
public:
  ConstraintExpression<T>& Not()
  {
    builder.Append(new NotOperator<T>());
    return *this;
  }

  ConstraintExpression<T>& EqualTo(T expectation)
  {
    builder.Append(new EqualToOperator<T>(expectation));
    return *this;
  }

  bool Assert(T actual)
  {
    Operator<T>* op = builder.Build();
    return op->Evaluate(actual);
  }

private:
  ExpressionBuilder<T> builder;
};

template <typename T>
ConstraintExpression<T> Is()
{
  return ConstraintExpression<T>();
}



#endif	/* _IS_H */

