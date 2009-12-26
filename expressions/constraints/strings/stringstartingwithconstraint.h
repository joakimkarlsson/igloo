/* 
 * File:   stringstartingwithconstraint.h
 * Author: joakim
 *
 * Created on December 25, 2009, 10:28 PM
 */

#ifndef _STRINGSTARTINGWITHCONSTRAINT_H
#define	_STRINGSTARTINGWITHCONSTRAINT_H

namespace igloo {

  class StringStartingWithConstraint : public Constraint<std::string>
  {
  public:
    StringStartingWithConstraint(std::string expected) : _expected(expected) {}

    virtual bool Evaluate(std::string actual) const
    {
      return actual.find(_expected) == 0;
    }

    std::string ExpectationText() const
    {
       std::ostringstream str;
       str << "string starting with " << _expected;
       return str.str();
    }

  private:
    std::string _expected;
  };
}

#endif	/* _STRINGSTARTINGWITHCONSTRAINT_H */

