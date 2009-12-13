/* 
 * File:   logicaloperator.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:05 AM
 */

#ifndef _LOGICALOPERATOR_H
#define	_LOGICALOPERATOR_H

class LogicalOperator : public IOperator
{
public:

  virtual bool IsLogicalOperator()
  {
    return true;
  }
  virtual bool Evaluate(stack<bool>& boolStack) = 0;
};

#endif	/* _LOGICALOPERATOR_H */

