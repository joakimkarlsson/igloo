/* 
 * File:   equaltooperator.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:13 AM
 */

#ifndef _EQUALTOCONSTRAINT_H
#define	_EQUALTOCONSTRAINT_H

template <typename T>
class EqualToConstraint : public Constraint<T>
{
public:

  EqualToConstraint(T expected) : _expected(expected)
  {
  }

  bool Evaluate(T actual)
  {
    return actual == _expected;
  }

private:
  T _expected;
};

#endif

