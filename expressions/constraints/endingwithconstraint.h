#ifndef IGLOO_ENDINGWITHCONSTRAINT_H
#define	IGLOO_ENDINGWITHCONSTRAINT_H

namespace igloo {

  class EndingWithConstraint : public Constraint<std::string>
  {
  public:

    EndingWithConstraint(const std::string& expected) : Constraint<std::string>(expected)
    {
    }

    virtual bool Evaluate(const std::string& actual) const
    {
      if(m_expected.size() > actual.size())
      {
        return false;
      }

      std::string endOfActual = actual.substr(actual.size()-m_expected.size());

      return m_expected.compare(endOfActual) == 0;
    }

    void ToString(std::string& str) const
    {
      std::ostringstream stm;
      stm << "string ending with " << m_expected;
      str += stm.str();
    }
  };
}

#endif

