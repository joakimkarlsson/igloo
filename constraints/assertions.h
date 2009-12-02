#ifndef _ASSERTIONS_H
#define	_ASSERTIONS_H
#include "equalto_constraint.h"

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
};

class Is
{
public:

  template <typename T>
  static auto_ptr<IConstraint<T> > EqualTo(T expectation)
  {
    return auto_ptr<IConstraint<T> >(new EqualToConstraint<T > (expectation));
  }
};

#endif	/* _ASSERTIONS_H */

