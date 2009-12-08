#ifndef _ASSERTIONS_H
#define	_ASSERTIONS_H
#include "not_constraint.h"
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

class ISyntaxHelper
{
public:
  template <typename T>
  auto_ptr<IConstraint<T> > EqualTo(T expectation) = 0;

};

class InverseSyntaxHelper : public ISyntaxHelper
{
public:
  InverseSyntaxHelper(SyntaxHelper* wrapped) : _wrapped(wrapped)
  {
  }
  
  template <typename T>
  auto_ptr<IConstraint<T> > EqualTo(T expectation)
  {
    return auto_ptr<IConstraint<T> >(new NotConstraint<T>(_wrapped.EqualTo(expectation)));
  }
};

class SyntaxHelper : public ISyntaxHelper
{
public:
  SyntaxHelper() : Not(this)
  {
  }

  template <typename T>
  auto_ptr<IConstraint<T> > EqualTo(T expectation)
  {
    return CreateConstraint<EqualToConstraint<T>, T>(expectation);
  }

  InverseSyntaxHelper Not;

protected:
  template <typename C, typename T>
  static auto_ptr<IConstraint<T> > CreateConstraint(T expectation)
  {
    return auto_ptr<IConstraint<T> >(new C(expectation));
  }
};

#endif	/* _ASSERTIONS_H */

