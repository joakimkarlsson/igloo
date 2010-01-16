#ifndef INCLUDED_EQUALSCONSTRAINT_H
#define INCLUDED_EQUALSCONSTRAINT_H

#include "expression.h"

template< typename ExpectedType >
struct EqualsConstraint : Expression< EqualsConstraint<ExpectedType> >
{
	EqualsConstraint(const ExpectedType& expected)
		: m_expected(expected)
	{
	}

	template<typename ActualType>
	bool operator()(const ActualType& actual) const
	{
		return (m_expected == actual);
	}

	ExpectedType m_expected;
};

template< typename ExpectedType >
EqualsConstraint<ExpectedType> Equals(const ExpectedType& expected)
{
	return EqualsConstraint<ExpectedType>(expected);
}

EqualsConstraint<std::string> Equals(const char* expected)
{
	return EqualsConstraint<std::string>(expected);
}

template< typename ExpectedType >
std::string Stringize(const EqualsConstraint<ExpectedType>& constraint)
{
  std::ostringstream builder;
  builder << "equal to " << constraint.m_expected;

  return builder.str();
}

#endif INCLUDED_EQUALSCONSTRAINT_H