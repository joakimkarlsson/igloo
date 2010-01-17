#ifndef IGLOO_ANDOPERATOR_H
#define	IGLOO_ANDOPERATOR_H

namespace igloo {

  class AndOperator : public Operator {
  public:

    virtual void Evaluate(std::stack<bool>& boolStack) const
    {
      bool right = boolStack.top();
      boolStack.pop();

      bool left = boolStack.top();
      boolStack.pop();

      boolStack.push(right && left);
    }
    
    virtual bool IsLeftAssociative() const
    {
      return true;
    }
  }; 

	inline std::string Stringize(const AndOperator&)
	{
		return "and";
	}
}


#endif

