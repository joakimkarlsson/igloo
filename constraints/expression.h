/* 
 * File:   Expression.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:42 AM
 */

#ifndef _EXPRESSION_H
#define	_EXPRESSION_H

class Expression
{
public:

  Expression& Not()
  {
    operators.Append(new NotOperator());
    return *this;
  }

  template <typename T>
  Expression& EqualTo(T expectation)
  {
    operators.Append(new EqualToConstraint<T > (expectation));
    return *this;
  }

  IOperator* PopOperator()
  {
    return operators.Pop();
  }

private:
  OperatorStack operators;
};

#endif

