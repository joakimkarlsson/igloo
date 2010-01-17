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

      virtual bool IsLeftAssociative() const
      {
        return false;
      }
   }; 

	inline std::string Stringize(const NotOperator&)
	{
		return "not";
	}

}
#endif

