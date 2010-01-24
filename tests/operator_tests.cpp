#include "igloo_self_test.h"

using namespace igloo;

TestFixture(OperatorTests)
{
  TestMethod(ShouldHandleAndOperatorExpressionTemplates)
  {
    Assert::That(5, IsLessThan(6) && IsGreaterThan(4));
  } 

  TestMethod(ShouldHandleAndOperator)
  {
    Assert::That(5, Is().LessThan(6).And().GreaterThan(4));
  }

  TestMethod(ShouldHandleAndOperatorFailExpressionTemplates)
  {
    AssertTestFails(Assert::That(5, IsLessThan(7) && IsGreaterThan(5)), "less than 7 and greater than 5");
  } 

  TestMethod(ShouldHandleAndOperatorFail)
  {
    AssertTestFails(Assert::That(5, Is().LessThan(7).And().GreaterThan(5)), "less than 7 and greater than 5");
  }

  TestMethod(ShouldHandleOrOperator)
  {
    Assert::That(12, Is().LessThan(7).Or().GreaterThan(5));
  } 

  TestMethod(ShouldHandleOrOperatorExpressionTemplates)
  {
    Assert::That(12, IsLessThan(7) || IsGreaterThan(5));
  }

  TestMethod(ShouldHandleOrOperatorFails)
  {
    AssertTestFails(Assert::That(67, Is().LessThan(12).Or().GreaterThan(99)), "less than 12 or greater than 99");
  }
   
  TestMethod(ShouldHandleOrOperatorFailsExpressionTemplates)
  {
    AssertTestFails(Assert::That(67, IsLessThan(12) || IsGreaterThan(99)), "less than 12 or greater than 99");
  }
  
  TestMethod(ShouldHandleNotOperators)
  {
    Assert::That(5, Is().Not().EqualTo(4));
  }

  TestMethod(ShouldHandleNotOperatorsExpressionTemplates)
  {
    Assert::That(5, !Equals(4));
  }

  TestMethod(ShouldHandleNotOperatorsFails)
  {
    AssertTestFails(Assert::That(12, Is().Not().EqualTo(12)), "not equal to 12");
  } 

  TestMethod(ShouldHandleNotOperatorsFailsExpressionTemplates)
  {
    AssertTestFails(Assert::That(12, !Equals(12)), "not equal to 12");
  }

  TestMethod(ShouldHandleNotOperatorsForStrings)
  {
    Assert::That("joakim", Is().Not().EqualTo("harry"));
  } 

  TestMethod(ShouldHandleNotOperatorsForStringsExpressionTemplates)
  {
    Assert::That("joakim", !Equals("harry"));
  }

  TestMethod(ShouldHandleBothLeftAndRightAssociativeOperators)
  {
    Assert::That(5, Is().GreaterThan(4).And().Not().LessThan(3));
  } 

  TestMethod(ShouldHandleBothLeftAndRightAssociativeOperatorsExpressionTemplates)
  {
    Assert::That(5, IsGreaterThan(4)&& !IsLessThan(3));
  }
  
  TestMethod(ShouldHandleAllOperator)
  {
    std::vector<int> v;
    v.push_back(3);
    v.push_back(5);
    
    Assert::That(v, Is().All().GreaterThan(1).Or().LessThan(4));
    
  }
};
