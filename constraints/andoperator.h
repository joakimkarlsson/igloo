/* 
 * File:   andoperator.h
 * Author: joakim
 *
 * Created on December 18, 2009, 11:45 PM
 */

#ifndef _ANDOPERATOR_H
#define	_ANDOPERATOR_H

namespace igloo {

  class AndOperator : public Operator {
  public:

    virtual void Evaluate(std::stack<bool>& boolStack) const
    {
      bool right = boolStack.top();
      boolStack.pop();

      bool left = boolStack.top();
      boolStack.pop();

      boolStack.push(right && left);
    }

    virtual std::string ExpectationText() const
    {
      return "and";
    }
    
    virtual bool IsLeftAssociative() const
    {
      return true;
    }
  };
}


#endif	/* _ANDOPERATOR_H */

