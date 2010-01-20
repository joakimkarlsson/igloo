#ifndef INCLUDED_CONTAINSCONSTRAINT_H
#define INCLUDED_CONTAINSCONSTRAINT_H

#include <algorithm>

namespace igloo {
  
  template <typename ContainerType>
  struct find_in_container_traits
  {
    template <typename ExpectedType>
    static bool find(const ContainerType& container, const ExpectedType& expected)
    {
      return std::find(container.begin(), container.end(), expected) != container.end();
    }
  };
  
  template <typename KeyType, typename ValueType>
  struct find_in_container_traits<std::map<KeyType, ValueType> >
  {
    template <typename ExpectedType>
    static bool find(const std::map<KeyType, ValueType>& container, const ExpectedType& expected)
    {
      return container.find(expected) != container.end();
    }
  };
  
	template <typename ExpectedType>
	struct ContainsConstraint : Expression< ContainsConstraint<ExpectedType> >
	{
		ContainsConstraint(const ExpectedType& expected) 
    : m_expected(expected) {}
    
		template <typename ActualType>
		bool operator()(const ActualType& actual) const
		{
      return find_in_container_traits<ActualType>::find(actual, m_expected);
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