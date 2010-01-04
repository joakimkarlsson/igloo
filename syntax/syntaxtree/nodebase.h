#ifndef IGLOO_NODEBASE_H
#define IGLOO_NODEBASE_H

#include "iexpressionowner.h"

namespace igloo {

  class NodeBase
  {
  public:
    NodeBase(Expression& expression) : m_expression(expression) {}  

  protected:
    Expression& GetExpression()
    {
      return m_expression;
    }

  private:
    Expression& m_expression;    
  };

}

#endif
