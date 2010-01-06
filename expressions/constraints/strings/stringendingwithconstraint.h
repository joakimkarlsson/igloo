#ifndef IGLOO_STRINGENDINGWITHCONSTRAINT_H
#define	IGLOO_STRINGENDINGWITHCONSTRAINT_H

namespace igloo {

  class StringEndingWithConstraint : public Constraint<std::string>
  {
  public:

    StringEndingWithConstraint(std::string expected) : Constraint<std::string>(expected)
    {
    }

    virtual bool Evaluate(std::string actual) const
    {
      if(_expected.size() > actual.size())
      {
        return false;
      }

      std::string endOfActual = actual.substr(actual.size()-_expected.size());

      return _expected.compare(endOfActual) == 0;
    }

    void ToString(std::string& str) const
    {
      std::ostringstream stm;
      stm << "string ending with " << _expected;
      str += stm.str();
    }
  };
}

#endif

