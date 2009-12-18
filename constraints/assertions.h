#ifndef _ASSERTIONS_H
#define	_ASSERTIONS_H
#include <stack>
#include "ioperator.h"
#include "logicaloperator.h"
#include "constraint.h"
#include "notoperator.h"
#include "equaltoconstraint.h"
#include "greaterthanconstraint.h"
#include "operatorstack.h"
#include "expression.h"
#include "is.h"

namespace igloo {
   class Assert
   {
   public:
      template <typename T>
      static void That(T actual, Expression& constraint)
      {
         std::stack<bool> operatorResultsStack;
         std::stack<std::string> expectationTexts;

         IOperator* op;
         while ((op = constraint.PopOperator()) != NULL)
         {
            PerformOperation(op, actual, operatorResultsStack, expectationTexts);
         }

         if (!operatorResultsStack.top())
         {
            throw AssertionException(CreateErrorText(expectationTexts, actual));
         }
      }

      static void That(const char* actual, Expression& constraint)
      {
         return That<std::string>(std::string(actual), constraint);
      }

      static void That(bool& actual)
      {
         if (!actual)
         {
            throw AssertionException("Expected condition to be true");
         }
      }

   private:

      template <typename T>
      static void PerformOperation(IOperator * op, T actual, std::stack<bool>& resultStack, std::stack<std::string>& expectationTexts)
      {
         expectationTexts.push(op->ExpectationText());

         if (op->IsLogicalOperator())
         {
            LogicalOperator* logical = dynamic_cast<LogicalOperator*> (op);
            logical->Evaluate(resultStack);
         }
         else
         {
            Constraint<T>* constraint = dynamic_cast<Constraint<T>*> (op);
            resultStack.push(constraint->Evaluate(actual));
         }

         delete op;
      }

      template <typename T>
      static std::string CreateErrorText(std::stack<std::string>& expectationTexts, T actual)
      {
         std::ostringstream str;
         str << "Expected: ";

         while (!expectationTexts.empty())
         {
            str << expectationTexts.top();
            expectationTexts.pop();

            if (!expectationTexts.empty())
            {
               str << " ";
            }
         }
         str << std::endl;

         str << "Actual: " << actual << std::endl;

         return str.str();
      }
   };
}
#endif	/* _ASSERTIONS_H */

