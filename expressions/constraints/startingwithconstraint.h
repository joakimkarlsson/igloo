#ifndef IGLOO_STARTINGWITHCONSTRAINT_H
#define	IGLOO_STARTINGWITHCONSTRAINT_H

namespace igloo {

  class StartingWithConstraint : public Constraint<std::string>
  {
  public:
    StartingWithConstraint(const std::string& expected) : Constraint<std::string>(expected) {}

    bool Evaluate(const std::string& actual) const
    {
      return actual.find(m_expected) == 0;
    }

    void ToString(std::string& str) const
    {
       std::ostringstream stm;
       stm << "string starting with " << m_expected;
       str += stm.str();
    }
  };
}

#endif

