#ifndef IGLOO_STRINGSTARTINGWITHCONSTRAINT_H
#define	IGLOO_STRINGSTARTINGWITHCONSTRAINT_H

namespace igloo {

  class StringStartingWithConstraint : public Constraint<std::string>
  {
  public:
    StringStartingWithConstraint(std::string expected) : Constraint<std::string>(expected) {}

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

