#ifndef IGLOO_INODEOWNER_H
#define IGLOO_INODEOWNER_H

namespace igloo {

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
