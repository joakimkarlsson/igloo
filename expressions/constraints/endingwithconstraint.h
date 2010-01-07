#ifndef IGLOO_ENDINGWITHCONSTRAINT_H
#define	IGLOO_ENDINGWITHCONSTRAINT_H

namespace igloo {

  class EndingWithConstraint : public Constraint<std::string>
  {
  public:

    EndingWithConstraint(std::string expected) : Constraint<std::string>(expected)
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

