#ifndef IGLOO_ASSERT_H
#define	IGLOO_ASSERT_H

#include "syntax.h"

namespace igloo {

  class Assert {
  public:

    template <typename T>
    static void That(T actual, CompleteStatement& statement)
    {
      if (!statement.Evaluate(actual))
      {
        throw AssertionException(CreateErrorText(statement.ExpressionAsString(), actual));
      }
    }

    static void That(const char* actual, CompleteStatement& node)
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

    static void Failure(const std::string& message)
    {
        std::string adorned = "Forced failure: ";
        adorned += message;

        throw AssertionException(adorned);
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
#endif	// IGLOO_ASSERT_H

