#ifndef IGLOO_ASSERT_H
#define IGLOO_ASSERT_H

#include "stringize.h"

namespace igloo {

   template <typename Container>
   struct SequentialContainerStringizer
   {
      static std::string Stringize(const Container& cont)
      {
         std::ostringstream stm;
         typedef Container::const_iterator Iterator;

         stm << "[ ";
         for(Iterator it = cont.begin(); it != cont.end();)
         {
            stm << igloo::Stringize(*it);

            if(++it != cont.end()) 
            {
               stm << ", ";
            }
         }
         stm << " ]";
         return stm.str();
      };
   };

   template< typename T >
   std::string Stringize(const std::vector<T>& t)
   {
      return SequentialContainerStringizer<std::vector<T> >::Stringize(t);
   }

   template< typename T >
   std::string Stringize(const std::deque<T>& t)
   {
      return SequentialContainerStringizer<std::deque<T> >::Stringize(t);
   }

   template< typename T >
   std::string Stringize(const std::list<T>& t)
   {
      return SequentialContainerStringizer<std::list<T> >::Stringize(t);
   }

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
               std::string expected = Stringize(expression);
               throw AssertionException(CreateErrorText(expected, actual));
            }      
         }
         catch (const InvalidExpressionException& e) 
         {
            throw AssertionException("Malformed expression: \"" + Stringize(expression) + "\"\n" + e.Message());
         }
      }

      template <typename ConstraintListType>
      static void That(const char* actual, ExpressionBuilder<ConstraintListType> expression)
      {
         return That<std::string>(std::string(actual), expression);
      }

      template <typename ActualType, typename ExpressionType>
      static void That(const ActualType& actual, const ExpressionType& evaluate)
      {
         if (!evaluate(actual))
         {
            std::string expected = Stringize(evaluate);
            throw AssertionException(CreateErrorText(expected, actual));
         }
      }

      template <typename ExpressionType>
      static void That(const char* actual, const ExpressionType& evaluate)
      {
         return That<std::string>(std::string(actual), evaluate);
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
         str << "Actual: " << Stringize(actual);
         str << std::endl;

         return str.str();
      }
   };
}

#endif	// IGLOO_ASSERT_H
