//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_COLLECTIONCONSTRAINTEVALUATOR_H
#define IGLOO_COLLECTIONCONSTRAINTEVALUATOR_H

#include <string>

namespace igloo
{

  template<typename ConstraintListType, typename ActualType>
    struct CollectionConstraintEvaluator
    {
      static unsigned int
      Evaluate(const ConstraintOperator& op, ConstraintListType& list,
          ResultStack& result, OperatorStack& operators,
          const ActualType& actual)
      {
        ConstraintOperator::EvaluateOperatorsWithLessOrEqualPrecedence(op,
            operators, result);

        unsigned int passed_elements = 0;
        typename ActualType::const_iterator it;
        for (it = actual.begin(); it != actual.end(); it++)
          {
            if (ConstraintOperator::EvaluateElementAgainstRestOfExpression(
                list, *it))
              {
                passed_elements++;
              }
          }

        return passed_elements;
      }
    };

  template<typename ConstraintListType>
    struct CollectionConstraintEvaluator<ConstraintListType, std::string>
    {
      static unsigned int
      Evaluate(const ConstraintOperator& op, ConstraintListType& list,
          ResultStack& result, OperatorStack& operators,
          const std::string& actual)
      {
        ConstraintOperator::EvaluateOperatorsWithLessOrEqualPrecedence(op,
            operators, result);

        unsigned int passed_elements = 0;
        std::string::size_type start_of_line = 0;
        std::string::size_type end_of_line = actual.find('\n');
        while (end_of_line != std::string::npos)
          {
            std::string line = actual.substr(start_of_line, end_of_line - start_of_line);
            if (ConstraintOperator::EvaluateElementAgainstRestOfExpression(list, line))
              {
                passed_elements++;
              }

            start_of_line = end_of_line + 1;
            end_of_line = actual.find('\n', start_of_line);
          }

        if(start_of_line < actual.size())
          {
            std::string line = actual.substr(start_of_line);
            if(ConstraintOperator::EvaluateElementAgainstRestOfExpression(list, line))
              {
                passed_elements++;
              }
          }

        return passed_elements;
      }
    };

}

#endif
