#ifndef _ROOTSYNTAX_H_
#define _ROOTSYNTAX_H_

#include "expressionsyntax.h"
#include "stringsyntax.h"
#include "../expressions/expression.h"

namespace igloo {

  class RootSyntax : public ExpressionSyntax {
  public:

    RootSyntax(std::auto_ptr<Expression> expression) : ExpressionSyntax(expression)
    {
    }

    // Operators

    RootSyntax& Not()
    {
      _expression->Add(new NotOperator());
      return *this;
    }

    RootSyntax& And()
    {
      _expression->Add(new AndOperator());
      return *this;
    }

    // Constraints

    template <typename T>
    RootSyntax& EqualTo(T expectation)
    {
      _expression->Add(new EqualToConstraint<T > (expectation));
      return *this;
    }

    RootSyntax& EqualTo(const char* expectation)
    {
      return EqualTo<std::string > (std::string(expectation));
    }

    template <typename T>
    RootSyntax& GreaterThan(T expectation)
    {
      _expression->Add(new GreaterThanConstraint<T > (expectation));
      return *this;
    }

    template <typename T>
    RootSyntax& LessThan(T expectation)
    {
      _expression->Add(new LessThanConstraint<T > (expectation));
      return *this;
    }

    StringSyntax String()
    {
      StringSyntax stringSyntax(_expression);
      return stringSyntax;
    }
  };


}

#endif
