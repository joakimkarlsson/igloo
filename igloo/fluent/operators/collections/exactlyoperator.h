#ifndef IGLOO_EXACTLYOPERATOR_H
#define IGLOO_EXACTLYOPERATOR_H

namespace igloo {

   struct ExactlyOperator : public CollectionOperator
   {
      ExactlyOperator(unsigned int expected) : m_expected(expected) {}

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

         result.push(passed_elements == m_expected); 
      }

      unsigned int m_expected;
   };

  template<>
  struct Stringizer< ExactlyOperator >
  {
    static std::string ToString(const ExactlyOperator& op)
    {
      std::ostringstream stm;
      stm << "exactly " << op.m_expected;
      return stm.str();
    }
  };
}

#endif
