#ifndef _STRINGSYNTAX_H_
#define _STRINGSYNTAX_H_

#include "../expressions/constraints/strings/stringoflengthconstraint.h"

namespace igloo {

  class StringSyntax : public ExpressionSyntax {
  public:

    explicit StringSyntax(std::auto_ptr<Expression> expression) : ExpressionSyntax(expression)
    {
    }

    StringSyntax& And()
    {
      _expression->Add(new AndOperator());
      return *this;
    }

    StringSyntax& Not()
    {
      _expression->Add(new NotOperator());
      return *this;
    }

    StringSyntax& Containing(std::string expectation)
    {
      _expression->Add(new StringContainingConstraint(expectation));
      return *this;
    }

    StringSyntax& Containing(const char* expectation)
    {
      return Containing(std::string(expectation));
    }

    StringSyntax& StartingWith(std::string expectation)
    {
      _expression->Add(new StringStartingWithConstraint(expectation));
      return *this;
    }

    StringSyntax& EndingWith(std::string expectation)
    {
      _expression->Add(new StringEndingWithConstraint(expectation));
      return *this;
    }

    StringSyntax& OfLength(int expectation)
    {
      _expression->Add(new StringOfLengthConstraint(expectation));
      return *this;
    }
  };

}

#endif
