/* 
 * File:   constraint.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:07 AM
 */

#ifndef _CONSTRAINT_H
#define	_CONSTRAINT_H

namespace igloo {

  template <typename T>
  class Constraint : public IToken
  {
  public:

    Constraint(T expected) : _expected(expected) {}

    virtual bool IsOperator() const
    {
      return false;
    }

    virtual bool Evaluate(T actual) const = 0;

  protected:
    T _expected;
  };
}
#endif	/* _CONSTRAINT_H */

