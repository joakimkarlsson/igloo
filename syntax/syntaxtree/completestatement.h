#ifndef IGLOO_COMPLETESTATEMENT_H
#define IGLOO_COMPLETESTATEMENT_H

namespace igloo {

  class CompleteStatement : NodeBase
  {
  public:
    explicit CompleteStatement(Expression& expression) : NodeBase(expression) {}

    template <typename T>
    bool Evaluate(T actual)
    {
      return GetExpression().Evaluate(actual);
    }

    std::string ExpressionAsString()
    {
      return GetExpression().ToString();
    } 
  };

}

#endif
