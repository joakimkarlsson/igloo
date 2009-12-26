#ifndef _SYNTAX_H_
#define _SYNTAX_H_

#include "syntaxbase.h"
#include "stringsyntax.h"
#include "../expressions/expression.h"

namespace igloo {

  class Syntax : public SyntaxBase {
  public:

    Syntax(std::auto_ptr<Expression> expression) : SyntaxBase(expression)
    {
    }

    // Operators

    Syntax& Not()
    {
      _expression->Add(new NotOperator());
      return *this;
    }

    Syntax& And()
    {
      _expression->Add(new AndOperator());
      return *this;
    }

    // Constraints

    template <typename T>
    Syntax& EqualTo(T expectation)
    {
      _expression->Add(new EqualToConstraint<T > (expectation));
      return *this;
    }

    Syntax& EqualTo(const char* expectation)
    {
      return EqualTo<std::string > (std::string(expectation));
    }

    template <typename T>
    Syntax& GreaterThan(T expectation)
    {
      _expression->Add(new GreaterThanConstraint<T > (expectation));
      return *this;
    }

    template <typename T>
    Syntax& LessThan(T expectation)
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
