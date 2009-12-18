/* 
 * File:   notoperator.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:11 AM
 */

#ifndef _NOTOPERATOR_H
#define	_NOTOPERATOR_H

class NotOperator : public LogicalOperator
{
public:

   virtual void Evaluate(std::stack<bool>& boolStack)
  {
    bool currentResult = boolStack.top();
    boolStack.pop();
    boolStack.push(!currentResult);
  }

   virtual std::string ExpectationText()
  {
    return "not";
  }
};

#endif	/* _NOTOPERATOR_H */

