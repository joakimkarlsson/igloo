#ifndef IGLOO_STRINGCONSTRAINTOPERATIONS_H
#define IGLOO_STRINGCONSTRAINTOPERATIONS_H

#include "syntaxtree/iexpressionowner.h"

namespace igloo {

/*   template <typename ExpressionItemType> */
/*   class StringConstraintOperations : public Node<ExpressionItemType> */
/*   { */
/*   public: */
/*     explicit StringConstraintOperations(std::auto_ptr<ExpressionItemType> expressionItem) : Node<ExpressionItemType>(expressionItem) {} */

/*     ConstraintNode<StringConstraintOperations, ExpressionItem<std::string, ExpressionItemType> > Containing(std::string expected) */
/*     { */
/*       std::auto_ptr<ExpressionItem<std::string, ExpressionItemType> > nextExpressionItem(new ExpressionItem<std::string, ExpressionItemType>(new StringContainingConstraint(expected), Node<ExpressionItemType>::m_expressionItem)); */
/*       return ConstraintNode<StringConstraintOperations, ExpressionItem<std::string, ExpressionItemType> >(nextExpressionItem); */
/*     } */

/*     ConstraintNode<StringConstraintOperations, ExpressionItem<std::string, ExpressionItemType> > StartingWith(std::string expected) */
/*     { */
/*       std::auto_ptr<ExpressionItem<std::string, ExpressionItemType> > nextExpressionItem(new ExpressionItem<std::string, ExpressionItemType>(new StringStartingWithConstraint(expected), Node<ExpressionItemType>::m_expressionItem)); */
/*       return ConstraintNode<StringConstraintOperations, ExpressionItem<std::string, ExpressionItemType> >(nextExpressionItem); */
/*     } */

/*     ConstraintNode<StringConstraintOperations, ExpressionItem<std::string, ExpressionItemType> > EndingWith(std::string expected) */
/*     { */
/*       std::auto_ptr<ExpressionItem<std::string, ExpressionItemType> > nextExpressionItem(new ExpressionItem<std::string, ExpressionItemType>(new StringEndingWithConstraint(expected), Node<ExpressionItemType>::m_expressionItem)); */
/*       return ConstraintNode<StringConstraintOperations, ExpressionItem<std::string, ExpressionItemType> >(nextExpressionItem); */
/*     } */

/*    ConstraintNode<StringConstraintOperations, ExpressionItem<std::string, ExpressionItemType> > OfLength(int expected) */
/*     { */
/*       std::auto_ptr<ExpressionItem<std::string, ExpressionItemType> > nextExpressionItem(new ExpressionItem<std::string, ExpressionItemType>(new StringOfLengthConstraint(expected), Node<ExpressionItemType>::m_expressionItem)); */
/*       return ConstraintNode<StringConstraintOperations, ExpressionItem<std::string, ExpressionItemType> >(nextExpressionItem); */
/*     } */
/*   }; */
}

#endif
