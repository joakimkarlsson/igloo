
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_EQUALSCONTAINERCONSTRAINT_H
#define IGLOO_EQUALSCONTAINERCONSTRAINT_H

namespace igloo {

  template< typename ExpectedType >
    struct EqualsContainerConstraint : Expression< EqualsContainerConstraint<ExpectedType> >
  {
    EqualsContainerConstraint(const ExpectedType& expected)
      : expected_(expected)
    {}

    template<typename ActualType>
      bool operator()(const ActualType& actual) const
      {
        typename ActualType::const_iterator actual_it;
        typename ExpectedType::const_iterator expected_it;

        for(actual_it = actual.begin(), expected_it = expected_.begin(); actual_it != actual.end() && expected_it != expected_.end(); actual_it++, expected_it++)
        {
          if((*actual_it) != (*expected_it))
          {
            return false;
          }
        }

        return actual.size() == expected_.size();
      }

    const ExpectedType expected_;
  };

  template< typename ExpectedType >
    inline EqualsContainerConstraint<ExpectedType> EqualsContainer(const ExpectedType& expected)
    {
      return EqualsContainerConstraint<ExpectedType>(expected);
    }

  template< typename ExpectedType >
    struct Stringizer< EqualsContainerConstraint<ExpectedType> >
    {
      static std::string ToString(const EqualsContainerConstraint<ExpectedType>& constraint)
      {
        std::ostringstream builder;
        builder << igloo::Stringize(constraint.expected_);
        return builder.str();
      }
    };
}

#endif
