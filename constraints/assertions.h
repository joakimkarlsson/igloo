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

  static void That(bool& actual)
  {
    if(!actual)
      {
      throw AssertionException("Expected condition to be true");
    }
  }
};

class SyntaxHelperBase
{
protected:
  template <typename C, typename T>
  static auto_ptr<IConstraint<T> > CreateConstraint(T expectation)
  {
    return auto_ptr<IConstraint<T> >(new C(expectation));
  }
};

class InverseSyntaxHelper : public SyntaxHelperBase
{
public: 
  template <typename T>
  auto_ptr<IConstraint<T> > EqualTo(T expectation)
  {
    return auto_ptr<IConstraint<T> >(new NotConstraint<T>(CreateConstraint<EqualToConstraint<T>, T>(expectation)));
  }
};

class SyntaxHelper : public SyntaxHelperBase
{
public:
  template <typename T>
  auto_ptr<IConstraint<T> > EqualTo(T expectation)
  {
    return CreateConstraint<EqualToConstraint<T>, T>(expectation);
  }

  InverseSyntaxHelper Not;
};

#endif	/* _ASSERTIONS_H */

