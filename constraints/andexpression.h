#ifndef INCLUDED_ANDEXPRESSION_H
#define INCLUDED_ANDEXPRESSION_H

#include "expression_fwd.h"

template< typename LeftExpression, typename RightExpression >
struct AndExpression : Expression< AndExpression<LeftExpression, RightExpression> >
{
	AndExpression(const LeftExpression& left, const RightExpression& right)
		: m_left(left)
		, m_right(right)
	{
	}

	template< typename ActualType >
	bool operator()(const ActualType& actual) const
	{
		return (m_left(actual) && m_right(actual));
	}

	LeftExpression m_left;
	RightExpression m_right;
};

#endif INCLUDED_ANDEXPRESSION_H