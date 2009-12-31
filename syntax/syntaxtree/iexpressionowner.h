#ifndef IGLOO_IEXPRESSIONOWNER_H
#define IGLOO_IEXPRESSIONOWNER_H


namespace igloo {


  class IExpressionOwner
  {
  public:
    virtual Expression& GetExpression() = 0;
  };

}

#endif
