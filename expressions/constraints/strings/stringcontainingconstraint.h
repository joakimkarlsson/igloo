#ifndef _STRINGCONTAININGCONSTRAINT_H_
#define _STRINGCONTAININGCONSTRAINT_H_

namespace igloo {

  class StringContainingConstraint : public Constraint<std::string>, public IEvaluateConstraint<std::string>
  {
  public:

    StringContainingConstraint(std::string expected) : Constraint<std::string>(expected) {}

    virtual bool Evaluate(std::string actual) const
    {
      return actual.find(_expected) != actual.npos;
    }

    std::string ExpectationText() const
    {
       std::ostringstream str;
       str << "string containing " << _expected;
       return str.str();
    }
  };
}

#endif
