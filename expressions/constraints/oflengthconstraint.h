#ifndef IGLOO_OFLENGTHCONSTRAINT_H_
#define IGLOO_OFLENGTHCONSTRAINT_H_

namespace igloo {

  class OfLengthConstraint : public Constraint<unsigned int>
  {
  public:
    explicit OfLengthConstraint(int expectation) : Constraint<unsigned int>(expectation) {}


    template <typename ActualType>
    bool Evaluate(const ActualType& actual) const
    {
      return actual.size() == m_expected;
    }

    void ToString(std::string& str) const
    {
       std::ostringstream stm;
       stm << "of length " << m_expected;
       str += stm.str();
    }
  };
}

#endif
