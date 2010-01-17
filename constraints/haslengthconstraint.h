#ifndef INCLUDED_HASLENGTHCONSTRAINT_H
#define INCLUDED_HASLENGTHCONSTRAINT_H

namespace igloo {

	template <typename ExpectedType>
	struct HasLengthConstraint : Expression< HasLengthConstraint<ExpectedType> >
	{
		HasLengthConstraint(const ExpectedType& expected) 
			: m_expected(expected) {}
			
		template <typename ActualType>
		bool operator()(const ActualType& actual) const
		{
			return (actual.size() == m_expected);
		} 
		
		ExpectedType m_expected;
	};              

  template< typename ExpectedType >
	inline HasLengthConstraint<ExpectedType> HasLength(const ExpectedType& expected)
	{
		return HasLengthConstraint<ExpectedType>(expected);
	}
	
	inline HasLengthConstraint<std::string> HasLength(const char* expected)
	{
		return HasLengthConstraint<std::string>(expected);
	}

  template< typename ExpectedType >
  inline std::string Stringize(const HasLengthConstraint<ExpectedType>& constraint)
  {
    std::ostringstream builder;
    builder << "of length " << constraint.m_expected;

    return builder.str();
  }
}      

#endif