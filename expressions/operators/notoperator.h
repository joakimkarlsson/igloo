/* 
* File:   notoperator.h
* Author: joakim
*
* Created on December 13, 2009, 11:11 AM
*/

#ifndef _NOTOPERATOR_H
#define	_NOTOPERATOR_H

namespace igloo {
   class NotOperator : public Operator
   {
   public:

      virtual void Evaluate(std::stack<bool>& boolStack) const
      {
         bool currentResult = boolStack.top();
         boolStack.pop();
         boolStack.push(!currentResult);
      }

      virtual void ToString(std::string& str) const
      {
         str += "not";
      }

      virtual bool IsLeftAssociative() const
      {
        return false;
      }
   };
}
#endif	/* _NOTOPERATOR_H */

