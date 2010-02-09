#ifndef IGLOO_STARTSWITHCONSTRAINT_H
#define IGLOO_STARTSWITHCONSTRAINT_H

namespace igloo {

  template <typename ExpectedType>
  struct StartsWithConstraint : Expression< StartsWithConstraint<ExpectedType> >
  {
    StartsWithConstraint(const ExpectedType& expected) 
      : m_expected(expected) {}
      
    bool operator()(const std::string& actual) const
    {
      return actual.find(m_expected) == 0;
    } 
    
    ExpectedType m_expected;
  };              

  template< typename ExpectedType >
  inline StartsWithConstraint<ExpectedType> StartsWith(const ExpectedType& expected)
  {
    return StartsWithConstraint<ExpectedType>(expected);
  }
  
  inline StartsWithConstraint<std::string> StartsWith(const char* expected)
  {
    return StartsWithConstraint<std::string>(expected);
  }

  template< typename ExpectedType >
  struct Stringizer< StartsWithConstraint< ExpectedType > >
  {
    static std::string ToString(const StartsWithConstraint<ExpectedType>& constraint)
    {
      std::ostringstream builder;
      builder << "starts with " << Stringize(constraint.m_expected);

      return builder.str();
    }
  };
}

#endif
