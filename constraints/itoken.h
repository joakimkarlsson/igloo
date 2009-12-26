/* 
* File:   itoken.h
* Author: joakim
*
* Created on December 13, 2009, 11:02 AM
*/

#ifndef _ITOKEN_H
#define	_ITOKEN_H

namespace igloo {
   class IToken
   {
   public:
      virtual bool IsLogicalOperator() const = 0;
      virtual std::string ExpectationText() const = 0;
   };
}
#endif	/* _ITOKEN_H */

