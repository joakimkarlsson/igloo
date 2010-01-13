#ifndef IGLOO_CONTAININGCONSTRAINT_H_
#define IGLOO_CONTAININGCONSTRAINT_H_

#include <algorithm>
using std::find;

namespace igloo {

  template <typename ExpectedType>
  class ContainingConstraint : public Constraint<ExpectedType>
  {
    typedef Constraint<ExpectedType> Base;
  public:

    ContainingConstraint(ExpectedType expected) : Base(expected) {}

    template <typename ActualType>
    bool Evaluate(const ActualType& actual) const
    {
      return find(actual.begin(), actual.end(), Base::m_expected) != actual.end();
    }

    void ToString(std::string& str) const
    {
       std::ostringstream stm;
       stm << "containing " << Base::m_expected;
       str += stm.str();
    }
  };

  template <>
    class ContainingConstraint<std::string> : public Constraint<std::string>
  {
    typedef Constraint<std::string> Base;
  public:

    ContainingConstraint(const std::string& expected) : Base(expected) {}

    template <typename ActualType>
    bool Evaluate(const ActualType& actual) const
    {
      return actual.find(Base::m_expected) != actual.npos;
    }

    void ToString(std::string& str) const
    {
       std::ostringstream stm;
       stm << "string containing " << Base::m_expected;
       str += stm.str();
    }
  };

  template <>
    class ContainingConstraint<const char*> : public ContainingConstraint<std::string>
  {
    typedef ContainingConstraint<std::string> Base;
  public:

    ContainingConstraint(const char* expected) : Base(expected) {}

    template <typename ActualType>
    bool Evaluate(const ActualType& actual) const
    {
      return Base::Evaluate(std::string(actual));
    }
  };
}

#endif
