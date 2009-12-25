#ifndef _SYNTAXBASE_H_
#define _SYNTAXBASE_H_

namespace igloo {

  class Expression;

  class SyntaxBase
  {
public:
    SyntaxBase(Expression* expression) : _expression(expression) {}

    Expression& GetExpression()
    {
      return *_expression;
    }

  protected:
    Expression* _expression;
  };

}

#endif
