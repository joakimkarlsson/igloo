
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_ISOFTYPECONSTRAINT_H
#define IGLOO_ISOFTYPECONSTRAINT_H

#include <igloo/constraints/expressions/expression.h>
#include <typeinfo>

namespace igloo {
  
  template< typename ExpectedType >
  struct IsOfTypeConstraint : Expression< IsOfTypeConstraint<ExpectedType> >
  {   
    template<typename ActualType>
    bool operator()(const ActualType& actual) const
    {
      return (typeid(ExpectedType) == typeid(actual));
    }
  };
  
  template< typename ExpectedType >
  inline IsOfTypeConstraint<ExpectedType> IsOfType()
  {
    return IsOfTypeConstraint<ExpectedType>();
  }
  
  template< typename ExpectedType >
  struct Stringizer< IsOfTypeConstraint< ExpectedType > >
  {
    static std::string ToString(const IsOfTypeConstraint<ExpectedType>& constraint)
    {
      std::ostringstream builder;
      builder << "is of type " << igloo::Stringize(typeid(ExpectedType).name());
      
      return builder.str();
    }
  };
}

#endif
