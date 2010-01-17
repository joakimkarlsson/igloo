#ifndef INCLUDED_ENDSWITHCONSTRAINT_H
#define INCLUDED_ENDSWITHCONSTRAINT_H

namespace igloo {

	template <typename ExpectedType>
	struct EndsWithConstraint : Expression< EndsWithConstraint<ExpectedType> >
	{
		EndsWithConstraint(const ExpectedType& expected) 
			: m_expected(expected) {}
			
    bool operator()(const std::string& actual) const
		{
      size_t expectedPos = actual.length() - m_expected.length();
      return actual.find(m_expected) == expectedPos;
		} 
		
		ExpectedType m_expected;
	};              

  template< typename ExpectedType >
	inline EndsWithConstraint<ExpectedType> EndsWith(const ExpectedType& expected)
	{
		return EndsWithConstraint<ExpectedType>(expected);
	}
	
	inline EndsWithConstraint<std::string> EndsWith(const char* expected)
	{
		return EndsWithConstraint<std::string>(expected);
	}

  template< typename ExpectedType >
  inline std::string Stringize(const EndsWithConstraint<ExpectedType>& constraint)
  {
    std::ostringstream builder;
    builder << "starts with " << Stringize(constraint.m_expected);

    return builder.str();
  }
}      

#endif