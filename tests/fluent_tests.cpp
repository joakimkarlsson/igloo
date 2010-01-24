#include "igloo_self_test.h"

using namespace igloo;

TestFixture(FluentTests)
{
  TestMethod(SimpleEqualsContraints)
  {
    Assert::That(5, Iz().EqualTo(5).And().EqualTo(5).And().EqualTo(5));
  }
};

TestFixture(ConstraintListTests)
{
  TestMethod(CanConcatenateNilWithNil)
  {
    Nil list1;
    Nil list2;
    
    type_concat<Nil, Nil>::t result = Concatenate(list1, list2);
  }
};

