/* 
* File:   logicaloperator.h
* Author: joakim
*
* Created on December 13, 2009, 11:05 AM
*/

#ifndef _LOGICALOPERATOR_H
#define	_LOGICALOPERATOR_H
namespace igloo {
   class LogicalOperator : public IOperator
   {
   public:

      virtual bool IsLogicalOperator()
      {
         return true;
      }
      virtual void Evaluate(std::stack<bool>& boolStack) = 0;
   };
}
#endif	/* _LOGICALOPERATOR_H */

