#ifndef IGLOO_OPERATOR_H
#define	IGLOO_OPERATOR_H

namespace igloo {

   class Operator
   {
   public:
      virtual void Evaluate(std::stack<bool>& boolStack) const = 0;
      virtual bool IsLeftAssociative() const = 0;
      virtual void ToString(std::string& str) const = 0;
   };

}
#endif

