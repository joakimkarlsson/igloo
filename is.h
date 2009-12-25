/* 
* File:   is.h
* Author: joakim
*
* Created on December 9, 2009, 10:28 AM
*/

#ifndef _IS_H
#define	_IS_H

#include "syntax.h"

namespace igloo {
   

  Syntax Is()
   {
      return Syntax(new Expression());
   }
}
#endif	/* _IS_H */

