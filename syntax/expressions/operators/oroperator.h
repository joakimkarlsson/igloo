#ifndef IGLOO_OROPERATOR_H
#define IGLOO_OROPERATOR_H

namespace igloo {

  class OrOperator : public Operator
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
      
	inline std::string Stringize(const OrOperator&)
	{
		return "or";
	}
}

#endif
