#ifndef IGLOO_OROPERATOR_OLD_H
#define IGLOO_OROPERATOR_OLD_H

namespace igloo {

  class OrOperator_Old : public Operator
  {
  public:
    virtual void Evaluate(std::stack<bool>& boolStack) const
    {
      bool right = boolStack.top();
      boolStack.pop();

      bool left = boolStack.top();
      boolStack.pop();

      boolStack.push(left || right);
    }

    virtual bool IsLeftAssociative() const
    {
      return true;
    }
  };
      
	inline std::string Stringize(const OrOperator_Old&)
	{
		return "or";
	}
}

#endif
