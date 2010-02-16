
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_ASSERT_H
#define IGLOO_ASSERT_H

#include <igloo/core/stringize.h>

namespace igloo {

   class Assert
   {
   public:

      template <typename ActualType, typename ConstraintListType>
      static void That(const ActualType& actual, ExpressionBuilder<ConstraintListType> expression)
      {
         try 
         {
            ResultStack result;
            OperatorStack operators;
            expression.Evaluate(result, operators, actual);

            while(!operators.empty())
            {
               ConstraintOperator* op = operators.top();
               op->PerformOperation(result);
               operators.pop();
            }

            if(result.empty())
            {
               throw InvalidExpressionException("The expression did not yield any result");
            }

            if(!result.top())
            {
               std::string expected = igloo::Stringize(expression);
               throw AssertionException(CreateErrorText(expected, actual));
            }      
         }
         catch (const InvalidExpressionException& e) 
         {
            throw AssertionException("Malformed expression: \"" + igloo::Stringize(expression) + "\"\n" + e.Message());
         }
      }

      template <typename ConstraintListType>
      static void That(const char* actual, ExpressionBuilder<ConstraintListType> expression)
      {
         return That(std::string(actual), expression);
      }

      template <typename ActualType, typename ExpressionType>
      static void That(const ActualType& actual, const ExpressionType& evaluate)
      {
         if (!evaluate(actual))
         {
            std::string expected = igloo::Stringize(evaluate);
            throw AssertionException(CreateErrorText(expected, actual));
         }
      }

      template <typename ExpressionType>
      static void That(const char* actual, const ExpressionType& evaluate)
      {
         return That(std::string(actual), evaluate);
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
         throw AssertionException(message);
      }

   private:
      template <typename T>
      static std::string CreateErrorText(const std::string& expressionAsString, const T& actual)
      {
         std::ostringstream str;
         str << "Expected: ";
         str << expressionAsString;
         str << std::endl;
		 str << "Actual: " << igloo::Stringize(actual);
         str << std::endl;

         return str.str();
      }
   };
}

#endif	// IGLOO_ASSERT_H
