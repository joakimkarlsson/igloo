/* 
 * File:   ioperator.h
 * Author: joakim
 *
 * Created on December 13, 2009, 11:02 AM
 */

#ifndef _IOPERATOR_H
#define	_IOPERATOR_H

class IOperator
{
public:

  void SetNextOperator(IOperator* op)
  {
    _nextOperator = op;
  }

  virtual bool IsLogicalOperator() = 0;

protected:
  IOperator* _nextOperator;
};

#endif	/* _IOPERATOR_H */

