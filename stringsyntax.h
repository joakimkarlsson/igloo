#ifndef _STRINGSYNTAX_H_
#define _STRINGSYNTAX_H_

namespace igloo {

  class StringSyntax : public SyntaxBase
  {
  public:
    StringSyntax(Expression* expression) : SyntaxBase(expression) {}

    StringSyntax& Containing(std::string expectation)
    {
      _expression->Add(new StringContainingConstraint(expectation));
      return *this;
    }

    StringSyntax& Containing(const char* expectation)
    {
      return Containing(std::string(expectation));
    }
  };

}

#endif
