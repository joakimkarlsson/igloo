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

    virtual void ToString(std::string& str) const
    {
      str += "or";
    }

    virtual bool IsLeftAssociative() const
    {
      return true;
    }
  };

}

#endif
