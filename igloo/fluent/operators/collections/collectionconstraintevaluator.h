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
	static unsigned int Evaluate(const ConstraintOperator& op,
			ConstraintListType& expression, ResultStack& result,
			OperatorStack& operators, const ActualType& actual)
	{
		ConstraintOperator::EvaluateOperatorsWithLessOrEqualPrecedence(op,
				operators, result);

		unsigned int passed_elements = 0;
		typename ActualType::const_iterator it;
		for(it = actual.begin(); it != actual.end(); it++)
		{
			if(ConstraintOperator::EvaluateElementAgainstRestOfExpression(expression,
					*it))
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
	static unsigned int Evaluate(const ConstraintOperator& op,
			ConstraintListType& expression, ResultStack& result,
			OperatorStack& operators, const std::string& actual)
	{
		ConstraintOperator::EvaluateOperatorsWithLessOrEqualPrecedence(op,
				operators, result);

		unsigned int passed_elements = 0;
		std::string::size_type start_of_line = 0;
		std::string::size_type end_of_line = FindNewline(actual, start_of_line);
		while(end_of_line != std::string::npos)
		{
			if(EvaluateLine(expression, actual, start_of_line, end_of_line))
			{
				passed_elements++;
			}

			start_of_line = MoveToNextLine(actual, end_of_line);
			end_of_line = FindNewline(actual, start_of_line);
		}

		if(start_of_line < actual.size())
		{
			if(EvaluateLine(expression, actual, start_of_line))
			{
				passed_elements++;
			}
		}

		return passed_elements;
	}

private:
	static bool EvaluateLine(ConstraintListType& expression, const std::string& actual, std::string::size_type start_of_line,
	    std::string::size_type end_of_line = std::string::npos)
	{
    std::string line = actual.substr(start_of_line, end_of_line
         - start_of_line);
     return ConstraintOperator::EvaluateElementAgainstRestOfExpression(expression, line);
	}


	static std::string::size_type FindNewline(const std::string& actual,
			std::string::size_type start_pos)
	{
		return actual.find_first_of("\r\n", start_pos);
	}

	static std::string::size_type MoveToNextLine(const std::string& actual,
			std::string::size_type from_pos)
	{
		bool lf_found = false;
		while(from_pos < actual.size() && !lf_found)
		{
			if(actual[from_pos] == '\n')
			{
				lf_found = true;
			}
			from_pos++;
		}

		return from_pos;
	}
};

}

#endif
