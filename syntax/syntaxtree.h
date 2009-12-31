#ifndef IGLOO_SYNTAXTREE_H
#define IGLOO_SYNTAXTREE_H


namespace igloo {


  class IExpressionOwner
  {
  public:
    virtual Expression& GetExpression() = 0;
  };

  template <typename T>
  class UnaryNode;

  template <typename T>
  class BinaryNode;

  template <typename T>
  class ConstraintNode;

  template <typename T>
  class INodeOwner
  {
  public:
    virtual UnaryNode<T>& GetUnaryNode() = 0;
    virtual BinaryNode<T>& GetBinaryNode() = 0;
    virtual ConstraintNode<T>& GetConstraintNode() = 0;
  };
}

#endif
