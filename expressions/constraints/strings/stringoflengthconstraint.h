#ifndef _STRINGOFLENGTHCONSTRAINT_H_
#define _STRINGOFLENGTHCONSTRAINT_H_

namespace igloo {

  class StringOfLengthConstraint : public Constraint<unsigned int>, public IEvaluateConstraint<std::string>
  {
  public:
    explicit StringOfLengthConstraint(int expectation) : Constraint<unsigned int>(expectation) {}

    virtual bool Evaluate(std::string actual) const
    {
      return actual.size() == _expected;
    }

    std::string ExpectationText() const
    {
       std::ostringstream str;
       str << "string of length " << _expected;
       return str.str();
    }
  };
}

#endif
