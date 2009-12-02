#ifndef _EQUALITY_CONSTRAINT_H
#define	_EQUALITY_CONSTRAINT_H
#include "constraint.h"

template <typename T>
class EqualToConstraint : public IConstraint<T>
{
public:

  EqualToConstraint(T expectation) : _expectation(expectation)
  {
  }

  bool Assert(T actual, string& errorText)
  {
    if (actual == _expectation)
    {
      return true;
    }

    ostringstream errorStream;
    errorStream << "Expected: " << _expectation << ", actual: " << actual;

    errorText = errorStream.str();
    return false;
  }

private:
  T _expectation;
};
#endif	/* _EQUALITY_CONSTRAINT_H */

