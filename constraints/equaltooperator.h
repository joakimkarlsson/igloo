/* 
 * File:   equaltooperator.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:13 AM
 */

#ifndef _EQUALTOOPERATOR_H
#define	_EQUALTOOPERATOR_H

template <typename T>
class EqualToOperator : public Constraint<T>
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

#endif	/* _EQUALTOOPERATOR_H */

