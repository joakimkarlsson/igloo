/* 
 * File:   constraint.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:07 AM
 */

#ifndef _CONSTRAINT_H
#define	_CONSTRAINT_H

namespace igloo {

  template <typename ExpectedType>
  class Constraint
  {
  public:

  Constraint(ExpectedType expected) : _expected(expected) {}

  protected:
    ExpectedType _expected;
  };
}
#endif	/* _CONSTRAINT_H */

