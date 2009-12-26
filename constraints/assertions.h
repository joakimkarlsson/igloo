#ifndef _ASSERTIONS_H
#define	_ASSERTIONS_H
#include <stack>
#include "ioperator.h"
#include "logicaloperator.h"
#include "constraint.h"
#include "notoperator.h"
#include "andoperator.h"
#include "equaltoconstraint.h"
#include "greaterthanconstraint.h"
#include "stringcontainingconstraint.h"
#include "stringstartingwithconstraint.h"
#include "stringendingwithconstraint.h"
#include "lessthanconstraint.h"
//#include "operatorstack.h"
#include "expression.h"
#include "../is.h"

namespace igloo {

  class Assert {
  public:

    template <typename T>
    static void That(T actual, SyntaxBase& syntax)
    {
      if (!syntax.GetExpression().Evaluate(actual))
      {
        throw AssertionException(CreateErrorText(syntax.GetExpression(), actual));
      }
    }

    static void That(const char* actual, SyntaxBase& syntax)
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
#endif	/* _ASSERTIONS_H */

