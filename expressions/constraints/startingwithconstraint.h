#ifndef IGLOO_STARTINGWITHCONSTRAINT_H
#define	IGLOO_STARTINGWITHCONSTRAINT_H

namespace igloo {

  class StartingWithConstraint : public Constraint<std::string>
  {
  public:
    StartingWithConstraint(std::string expected) : Constraint<std::string>(expected) {}

    virtual bool Evaluate(std::string actual) const
    {
      return actual.find(_expected) == 0;
    }

    void ToString(std::string& str) const
    {
       std::ostringstream stm;
       stm << "string starting with " << _expected;
       str += stm.str();
    }
  };
}

#endif

