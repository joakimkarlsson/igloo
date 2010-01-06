#ifndef IGLOO_NOTOPERATOR_H
#define	IGLOO_NOTOPERATOR_H

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
#endif

