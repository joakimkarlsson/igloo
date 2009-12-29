#ifndef _ASSERT_H
#define	_ASSERT_H

#include "syntax.h"

namespace igloo {

  class Assert {
  public:

    template <typename T>
    static void That(T actual, ConstraintNode& statement)
    {
      if (!statement.Evaluate(actual))
      {
        throw AssertionException(CreateErrorText(statement.ExpressionAsString(), actual));
      }
    }

    static void That(const char* actual, ConstraintNode& node)
    {
      return That<std::string > (std::string(actual), node);
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
      static std::string CreateErrorText(std::string expressionAsString, const T& actual)
    {
      std::ostringstream str;
      str << "Expected: ";
      str << expressionAsString;
      str << std::endl;
      str << "Actual: " << actual;
      str << std::endl;

      return str.str();
    }
  };
}
#endif	/* _ASSERT_H */

