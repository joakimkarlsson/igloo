#ifndef IGLOO_STRINGCONTAININGCONSTRAINT_H_
#define IGLOO_STRINGCONTAININGCONSTRAINT_H_

namespace igloo {

  class StringContainingConstraint : public Constraint<std::string>
  {
  public:

    StringContainingConstraint(std::string expected) : Constraint<std::string>(expected) {}

    virtual bool Evaluate(std::string actual) const
    {
      return actual.find(_expected) != actual.npos;
    }

    void ToString(std::string& str) const
    {
       std::ostringstream stm;
       stm << "string containing " << _expected;
       str += stm.str();
    }
  };
}

#endif
