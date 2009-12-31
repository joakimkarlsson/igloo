#ifndef IGLOO_COMPLETESTATEMENT_H
#define IGLOO_COMPLETESTATEMENT_H

namespace igloo {

  class CompleteStatement : NodeBase
  {
  public:
    explicit CompleteStatement(IExpressionOwner& expressionOwner) : NodeBase(expressionOwner) {}

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
