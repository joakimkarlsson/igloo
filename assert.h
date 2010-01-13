#ifndef IGLOO_ASSERT_H
#define IGLOO_ASSERT_H

#include "syntax.h"
#include "stringize.h"

   template <typename T>
   struct stringize_trait
   {
      static std::string Stringize(const T& t)
      {
         return igloo::Stringize(t);
      }
   };

namespace igloo {

   class Assert
   {
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
         str << "Actual: " << stringize_trait<T>::Stringize(actual);
         str << std::endl;

         return str.str();
      }
   };
}

#endif	// IGLOO_ASSERT_H
