/* 
 * File:   is.h
 * Author: joakim
 *
 * Created on December 9, 2009, 10:28 AM
 */

#ifndef _IS_H
#define	_IS_H

#include <stack>
#include "ioperator.h"
#include "logicaloperator.h"
#include "constraint.h"
#include "notoperator.h"
#include "equaltooperator.h"
#include "expressionbuilder.h"
#include "constraintexpression.h"

ConstraintExpression Is()
{
  return ConstraintExpression();
}



#endif	/* _IS_H */

