#ifndef INCLUDED_NOTEXPRESSION_H
#define INCLUDED_NOTEXPRESSION_H

#include "expression_fwd.h"

namespace igloo {
	template< typename ExpressionType >
	struct NotExpression : Expression< NotExpression<ExpressionType> >
	{
		NotExpression(const ExpressionType& expression)
			: m_expression(expression)
		{
		}

		template<typename ActualType>
		bool operator()(const ActualType& actual) const
		{
			return !m_expression(actual);
		}

		ExpressionType m_expression;
	};

	template< typename ExpressionType >
	inline std::string Stringize(const NotExpression<ExpressionType>& expression)
	{
	  std::ostringstream builder;
	  builder << "not " << Stringize(expression.m_expression);

	  return builder.str();
	}

}
#endif