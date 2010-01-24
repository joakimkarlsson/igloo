#ifndef IGLOO_ANDOPERATOR_OLD_H
#define	IGLOO_ANDOPERATOR_OLD_H

namespace igloo {

  class AndOperator_OLD : public Operator {
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

	inline std::string Stringize(const AndOperator_OLD&)
	{
		return "and";
	}
}


#endif

