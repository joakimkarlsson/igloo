#ifndef _SYNTAXBASE_H_
#define _SYNTAXBASE_H_

namespace igloo {

  class Expression;

  class SyntaxBase
  {
public:
  explicit SyntaxBase(std::auto_ptr<Expression> expression) : _expression(expression) {}

    Expression& GetExpression()
    {
      return *(_expression.get());
    }

  protected:
    std::auto_ptr<Expression> _expression;
  };

}

#endif
