#ifndef _ASSERTIONS_H
#define	_ASSERTIONS_H
#include "not_constraint.h"
#include "equalto_constraint.h"
#include "is.h"

class Assert
{
public:

  template <typename T>
  static void That(T actual, auto_ptr<IConstraint<T> > constraint)
  {
    string errorText;
    if (!constraint->Assert(actual, errorText))
    {
      throw AssertionException(errorText);
    }
  }

  static void That(int actual, ConstraintExpression& constraint)
  {
    if(!constraint.Assert(actual))
    {
      throw AssertionException("WTF!?");
    }
  }

  static void That(bool& actual)
  {
    if(!actual)
      {
      throw AssertionException("Expected condition to be true");
    }
  }
};

#endif	/* _ASSERTIONS_H */

