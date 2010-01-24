#ifndef IGLOO_ASSERT_H
#define IGLOO_ASSERT_H

#include "syntax.h"
#include "stringize.h"

namespace igloo {
  
  template< typename T >
  std::string Stringize(const std::vector<T>& t)
  {
    std::ostringstream stm;
    stm << "vector (size: " << t.size() << ")";
    return stm.str();
  }
  
  class Assert
  {
  public:
    template <typename ActualType, typename SyntaxNodeType>
    static void That(const ActualType& actual, const ConstraintNode<SyntaxNodeType>& statement)
    {
      if (!statement.Evaluate(actual))
      {
        std::string str;
        statement.ToString(str);
        throw AssertionException(CreateErrorText(str, actual));
      }
    }
    
    template <typename SyntaxNodeType>
    static void That(const char* actual, const ConstraintNode<SyntaxNodeType>& node)
    {
      return That<std::string>(std::string(actual), node);
    }
    
    template <typename ActualType, typename ConstraintListType>
    static void That(const ActualType& actual, ExpressionBuilder<ConstraintListType> expression)
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
      
      std::cout << "Test result: " << result.top() << std::endl;      
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
