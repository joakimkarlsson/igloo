
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

Context(DetectingTypes)
{
  
  struct A {};
  struct B : public A {};
  
  Spec(CanAssertThatActualIsOfExcpetedType)
  {
    int x;
    Assert::That(x, Is().OfType<int>());
  }
  
  Spec(FailsForWrongType)
  {
    int x;
    AssertTestFails(Assert::That(x, Is().OfType<double>()) , "is of type");
  }
  
  Spec(FailsForDerivedType)
  {
    B b;
    AssertTestFails(Assert::That(b, IsOfType<A>()), "is of type");
  }
  
  Spec(SucceedsForExactType)
  {
    A a;
    Assert::That(a, IsOfType<A>());
  }
    
};
