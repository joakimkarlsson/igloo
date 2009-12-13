/* 
 * File:   constraint.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:07 AM
 */

#ifndef _CONSTRAINT_H
#define	_CONSTRAINT_H

template <typename T>
class Constraint : public IOperator
{
public:

  virtual bool IsLogicalOperator()
  {
    return false;
  }

  virtual bool Evaluate(T actual) = 0;
};

#endif	/* _CONSTRAINT_H */

