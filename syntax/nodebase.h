#ifndef IGLOO_NODEBASE_H
#define IGLOO_NODEBASE_H

#include "iexpressionowner.h"

namespace igloo {

  class NodeBase
  {
  public:
    NodeBase(IExpressionOwner& expressionOwner) : m_expressionOwner(expressionOwner) {}  

  protected:
    Expression& GetExpression()
    {
      return m_expressionOwner.GetExpression();
    }

  private:
    IExpressionOwner& m_expressionOwner;    
  };

}

#endif
