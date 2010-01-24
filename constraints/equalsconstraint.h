#ifndef INCLUDED_EQUALSCONSTRAINT_H
#define INCLUDED_EQUALSCONSTRAINT_H

#include "expressions/expression.h"

namespace igloo {
template< typename ExpectedType >
	struct EqualsConstraint : Expression< EqualsConstraint<ExpectedType> >
	{
    EqualsConstraint() {}
    EqualsConstraint(const EqualsConstraint& other) : m_expected(other.m_expected) {}
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
	inline EqualsConstraint<ExpectedType> Equals(const ExpectedType& expected)
	{
		return EqualsConstraint<ExpectedType>(expected);
	}

	inline EqualsConstraint<std::string> Equals(const char* expected)
	{
		return EqualsConstraint<std::string>(expected);
	}

template< typename ExpectedType >
	inline std::string Stringize(const EqualsConstraint<ExpectedType>& constraint)
	{
		std::ostringstream builder;
		builder << "equal to " << Stringize(constraint.m_expected);

		return builder.str();
	}
}
#endif
