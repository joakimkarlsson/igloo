#ifndef IGLOO_CONTAININGCONSTRAINT_H_
#define IGLOO_CONTAININGCONSTRAINT_H_

namespace igloo {

  class ContainingConstraint : public Constraint<std::string>
  {
  public:

    ContainingConstraint(std::string expected) : Constraint<std::string>(expected) {}

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
