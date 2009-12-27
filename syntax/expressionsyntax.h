#ifndef _EXPRESSIONSYNTAX_H_
#define _EXPRESSIONSYNTAX_H_

namespace igloo {

  class Expression;

  class ExpressionSyntax
  {
  public:

    explicit ExpressionSyntax(std::auto_ptr<Expression> expression) : _expression(expression)
    {
    }

    Expression& GetExpression()
    {
      return *(_expression.get());
    }

  protected:
    std::auto_ptr<Expression> _expression;
  };

}

#endif
