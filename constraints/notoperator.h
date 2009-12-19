/* 
* File:   notoperator.h
* Author: joakim
*
* Created on December 13, 2009, 11:11 AM
*/

#ifndef _NOTOPERATOR_H
#define	_NOTOPERATOR_H

namespace igloo {
   class NotOperator : public LogicalOperator
   {
   public:

      virtual void Evaluate(std::stack<bool>& boolStack) const
      {
         bool currentResult = boolStack.top();
         boolStack.pop();
         boolStack.push(!currentResult);
      }

      virtual std::string ExpectationText() const
      {
         return "not";
      }

      virtual LogicalOperator* Clone() const
      {
        return new NotOperator();
      }
   };
}
#endif	/* _NOTOPERATOR_H */

