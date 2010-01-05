#ifndef _ASSERT_H
#define	_ASSERT_H

#include "syntax.h"

namespace igloo {

  class Assert {
  public:

    template <typename ActualType, typename SyntaxNodeType>
    static void That(ActualType actual, const SyntaxNodeType& statement)
    {
      if (!statement.Evaluate(actual))
      {
        std::string str;
        statement.ToString(str);
        throw AssertionException(CreateErrorText(str, actual));
      }
    }

    template <typename SyntaxNodeType>
    static void That(const char* actual, const SyntaxNodeType& node)
    {
      return That<std::string > (std::string(actual), node);
    }

    static void That(bool actual)
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
    static std::string CreateErrorText(const std::string& expressionAsString, const T& actual)
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

