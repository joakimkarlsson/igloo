#ifndef IGLOO_CONSTRAINTOPERATIONS_H
#define IGLOO_CONSTRAINTOPERATIONS_H

#include "syntaxtree/iexpressionowner.h"
#include "syntaxtree/node.h"

namespace igloo {

  template <typename ExpressionItemType>
  class ConstraintOperations : public Node<ExpressionItemType>
  {
  public:
    explicit ConstraintOperations(std::auto_ptr<ExpressionItemType> expressionItem) : Node<ExpressionItemType>(expressionItem) {}
    ConstraintOperations(const ConstraintOperations<ExpressionItemType>& rhs) : Node<ExpressionItemType>(rhs) {}

    template <typename OperandType>
      ConstraintNode<ExpressionItem<EqualToConstraint<OperandType>, ExpressionItemType> > EqualTo(OperandType expected)
    {
      typedef ExpressionItem<EqualToConstraint<OperandType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<EqualToConstraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new EqualToConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<NextExpressionItemType>(expressionItem);
    }

    ConstraintNode<ExpressionItem<EqualToConstraint<std::string>, ExpressionItemType> > EqualTo(const char* expected)
    {
      return EqualTo<std::string>(std::string(expected));
    }

    template <typename OperandType>
    ConstraintNode<ExpressionItem<GreaterThanConstraint<OperandType>, ExpressionItemType> > GreaterThan(OperandType expected)
    {
      typedef ExpressionItem<GreaterThanConstraint<OperandType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<GreaterThanConstraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new GreaterThanConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<NextExpressionItemType>(expressionItem);
    }

    template <typename OperandType>
      ConstraintNode<ExpressionItem<LessThanConstraint<OperandType>, ExpressionItemType> > LessThan(OperandType expected)
    {
      typedef ExpressionItem<LessThanConstraint<OperandType>, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<LessThanConstraint<OperandType> > Constraint_ptr;

      std::auto_ptr<NextExpressionItemType> expressionItem(new NextExpressionItemType(Constraint_ptr(new LessThanConstraint<OperandType>(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<NextExpressionItemType>(expressionItem);
    }

    ConstraintNode<ExpressionItem<StringContainingConstraint, ExpressionItemType> > Containing(std::string expected)
    {
      typedef ExpressionItem<StringContainingConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringContainingConstraint> Constraint_ptr;
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringContainingConstraint(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<NextExpressionItemType>(nextExpressionItem);
    }

    ConstraintNode<ExpressionItem<StringStartingWithConstraint, ExpressionItemType> > StartingWith(std::string expected)
    {
      typedef ExpressionItem<StringStartingWithConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringStartingWithConstraint> Constraint_ptr;
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringStartingWithConstraint(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<NextExpressionItemType>(nextExpressionItem);
    }

    ConstraintNode<ExpressionItem<StringEndingWithConstraint, ExpressionItemType> > EndingWith(std::string expected)
    {
      typedef ExpressionItem<StringEndingWithConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringEndingWithConstraint> Constraint_ptr;
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringEndingWithConstraint(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<NextExpressionItemType>(nextExpressionItem);
    }

   ConstraintNode<ExpressionItem<StringOfLengthConstraint, ExpressionItemType> > OfLength(int expected)
    {
      typedef ExpressionItem<StringOfLengthConstraint, ExpressionItemType> NextExpressionItemType;
      typedef std::auto_ptr<StringOfLengthConstraint> Constraint_ptr;
      std::auto_ptr<NextExpressionItemType> nextExpressionItem(new NextExpressionItemType(Constraint_ptr(new StringOfLengthConstraint(expected)), Node<ExpressionItemType>::m_expressionItem));
      return ConstraintNode<NextExpressionItemType>(nextExpressionItem);
    }

  };

/*   template <typename ExpressionItemType> */
/*   class ConstraintOperationsNodeFactory */
/*   { */
/*   public: */
/*     typedef ConstraintOperations<ExpressionItemType, ConstraintOperationsNodeFactory<ExpressionItemType> > ConstraintOperationsType; */
/*     typedef ConstraintNode<ConstraintOperationsType, ExpressionItemType, ConstraintOperationsNodeFactory<ExpressionItemType> > ConstraintNodeType; */
/*     typedef BinaryNode<ConstraintOperationsType, ExpressionItemType, ConstraintOperationsNodeFactory<ExpressionItemType> > BinaryNodeType; */
/*     typedef UnaryNode<ConstraintOperationsType, ExpressionItemType, ConstraintOperationsNodeFactory<ExpressionItemType> > UnaryNodeType; */

/*     template <typename NewExpressionItemType> */
/*       static ConstraintOperationsNodeFactory<NewExpressionItemType> CreateNodeFactory() */
/*     { */
/*       return ConstraintOperationsNodeFactory<NewExpressionItemType>(); */
/*     } */

/*     ConstraintNodeType CreateConstraintNode(std::auto_ptr<ExpressionItemType> expressionItem) */
/*     { */
/*       return ConstraintNodeType(expressionItem); */
/*     } */

/*     BinaryNodeType CreateBinaryNode(std::auto_ptr<ExpressionItemType> expressionItem) */
/*     { */
/*       return BinaryNodeType(expressionItem); */
/*     } */

/*     UnaryNodeType CreateUnaryNode(std::auto_ptr<NewExpressionItemType> expressionItem) */
/*     { */
/*       return UnaryNodeType(expressionItem); */
/*     } */
/*   }; */
}

#endif
