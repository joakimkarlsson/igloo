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
  virtual bool IsLogicalOperator() = 0;
  virtual string ExpectationText() = 0;
};

#endif	/* _IOPERATOR_H */

