
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include <stdexcept>

using namespace igloo;

class ClassWithExceptions
{
public:
  int Method()
  {
    throw std::logic_error("ouch!");
  }
};

Context(MethodsWithExceptions)
{
  ClassWithExceptions objectUnderTest;  
  
  Spec(CanDetectExceptions)
  {  
    Assert::That(Thrown<std::logic_error>(objectUnderTest, &ClassWithExceptions::Method).what(), Is().EqualTo("ouch!"));
  }  
};


