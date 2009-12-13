/* 
 * File:   constraintexpression.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:42 AM
 */

#ifndef _CONSTRAINTEXPRESSION_H
#define	_CONSTRAINTEXPRESSION_H

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

#endif	/* _CONSTRAINTEXPRESSION_H */

