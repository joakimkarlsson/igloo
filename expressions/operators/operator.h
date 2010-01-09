#ifndef IGLOO_OPERATOR_H
#define	IGLOO_OPERATOR_H

namespace igloo {

   class Operator
   {
     typedef std::stack<const Operator*> OperatorStack;
     typedef std::stack<bool> ResultStack;

   public:
     void Evaluate(OperatorStack& opStack, ResultStack& resultStack)
     {
       if(IsLeftAssociative())
       {
         EvaluateOperatorsOnStack(opStack, resultStack);
       }

       opStack.push(this);
     }

     static void EvaluateOperatorsOnStack(OperatorStack& opStack, ResultStack& resultStack)
     {
       while(!opStack.empty())
       {
         opStack.top()->Evaluate(resultStack);
         opStack.pop();
       }
     }

     virtual void Evaluate(ResultStack& boolStack) const = 0;
     virtual bool IsLeftAssociative() const = 0;
     virtual void ToString(std::string& str) const = 0;
   };

}
#endif

