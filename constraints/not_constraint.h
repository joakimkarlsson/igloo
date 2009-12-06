/* 
 * File:   not_constraint.h
 * Author: joakim
 *
 * Created on December 3, 2009, 9:34 PM
 */

#ifndef _NOT_CONSTRAINT_H
#define	_NOT_CONSTRAINT_H
#include "constraint.h"

template <typename T>
class NotConstraint : public IConstraint<T>
{
public:

  NotConstraint(auto_ptr<IConstraint<T> > wrapped) : _wrapped(wrapped)
  {
  }

  virtual bool Assert(T actual, string& errorText)
  {
    return !_wrapped->Assert(actual, errorText);
  }

private:
  auto_ptr<IConstraint<T> > _wrapped;
};

#endif	/* _NOT_CONSTRAINT_H */

