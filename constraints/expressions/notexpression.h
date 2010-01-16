#ifndef INCLUDED_NOTEXPRESSION_H
#define INCLUDED_NOTEXPRESSION_H

#include "expression_fwd.h"

template< typename ExpressionType >
struct NotExpression : Expression< NotExpression<ExpressionType> >
{
	NotExpression(const ExpressionType& expression)
		: expression(expression)
	{
	}

	template<typename ActualType>
	bool operator()(const ActualType& actual) const
	{
		return !expression(actual);
	}

	ExpressionType expression;
};

template< typename ExpressionType >
inline std::string Stringize(const NotExpression<ExpressionType>& expression)
{
  std::ostringstream builder;
  builder << "not " << Stringize(expression.expression);

  return builder.str();
}

#endif INCLUDED_NOTEXPRESSION_H