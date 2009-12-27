#ifndef _ASSERT_H
#define	_ASSERT_H

#include "syntax.h"

namespace igloo {

  class Assert {
  public:

    template <typename T>
    static void That(T actual, ExpressionSyntax& syntax)
    {
      if (!syntax.GetExpression().Evaluate(actual))
      {
        throw AssertionException(CreateErrorText(syntax.GetExpression(), actual));
      }
    }

    static void That(const char* actual, ExpressionSyntax& syntax)
    {
      return That<std::string > (std::string(actual), syntax);
    }

    static void That(bool& actual)
    {
      if (!actual)
      {
        throw AssertionException("Expected: true\nActual: false");
      }
    }

  private:
    template <typename T>
    static std::string CreateErrorText(const Expression& expression, const T& actual)
    {
      std::ostringstream str;
      str << "Expected: ";
      str << expression.GetExpectationText();
      str << std::endl;
      str << "Actual: " << actual;
      str << std::endl;

      return str.str();
    }
  };
}
#endif	/* _ASSERT_H */

