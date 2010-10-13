
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
  int LogicError()
  {
    throw std::logic_error("not logical!");
  }
  
  double RangeError()
  {
    throw std::range_error("range error!");
  }
};

Context(MethodsWithExceptions)
{
  ClassWithExceptions objectUnderTest;  
  
  Spec(CanDetectExceptions)
  {  
    Assert::That(Thrown<std::logic_error>(objectUnderTest, &ClassWithExceptions::LogicError).what(), Is().EqualTo("not logical!"));
  }  
  
  Spec(CanDetectWrongException)
  {
    AssertTestFails(Assert::That(Thrown<std::logic_error>(objectUnderTest, &ClassWithExceptions::RangeError).what(), Is().EqualTo("not logical!")),
               "An exception of the wrong type was thrown");
  }
};


