/* 
 * File:   constraint.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:07 AM
 */

#ifndef _CONSTRAINT_H
#define	_CONSTRAINT_H

namespace igloo {

  template <typename OperandType>
  class Constraint
  {
  public:

    Constraint(OperandType expected) : _expected(expected) {}

    virtual bool IsOperator() const
    {
      return false;
    }

  protected:
    OperandType _expected;
  };
}
#endif	/* _CONSTRAINT_H */

