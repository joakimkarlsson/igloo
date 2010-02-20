
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_NONEOPERATOR_H
#define IGLOO_NONEOPERATOR_H

namespace igloo {

   struct NoneOperator : public CollectionOperator
   {
      template <typename ConstraintListType, typename ActualType>
      void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
      {
         EvaluateOperatorsWithLessOrEqualPrecedence(operators, result);

         unsigned int passed_elements = 0;
         typename ActualType::const_iterator it;
         for(it = actual.begin(); it != actual.end(); it++)
         {
            if(EvaluateElementAgainstRestOfExpression(list, *it))
            {
              passed_elements++;
            }
         }

         result.push(passed_elements == 0);
      }
   };

   template<>
   struct Stringizer<NoneOperator>
   {
      static std::string ToString(const NoneOperator&)
      {
         return "none";
      }
   };

}

#endif
