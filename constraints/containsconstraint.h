#ifndef INCLUDED_CONTAINSCONSTRAINT_H
#define INCLUDED_CONTAINSCONSTRAINT_H
  
#include <algorithm>
using std::find;

namespace igloo {

	template <typename ExpectedType>
	struct ContainsConstraint : Expression< ContainsConstraint<ExpectedType> >
	{
		ContainsConstraint(const ExpectedType& expected) 
			: m_expected(expected) {}
			
		template <typename ActualType>
		bool operator()(const ActualType& actual) const
		{
			return find(actual.begin(), actual.end(), m_expected) != actual.end();
		} 
		         
		bool operator()(const std::string& actual) const
		{
			return actual.find(m_expected) != actual.npos; 
		} 
		
		ExpectedType m_expected;
	};              
	
	
	
		template< typename ExpectedType >
		inline ContainsConstraint<ExpectedType> Contains(const ExpectedType& expected)
		{
			return ContainsConstraint<ExpectedType>(expected);
		}        
		
		inline ContainsConstraint<std::string> Contains(const char* expected)
		{
			return ContainsConstraint<std::string>(expected);
		}

	template< typename ExpectedType >
		inline std::string Stringize(const ContainsConstraint<ExpectedType>& constraint)
		{
			std::ostringstream builder;
			builder << "contains " << Stringize(constraint.m_expected);

			return builder.str();
		}
}      

#endif