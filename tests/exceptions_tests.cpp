
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include <stdexcept>

using namespace igloo;

#define AssertThrows(EXCEPTION_TYPE, METHOD) \
{ \
bool wrong_exception = false; \
try \
{ \
METHOD; \
Assert::Failure("No exception was thrown"); \
} \
catch (const EXCEPTION_TYPE& e) \
{ \
ExceptionStorage<EXCEPTION_TYPE>::last_exception = std::auto_ptr<EXCEPTION_TYPE>(new EXCEPTION_TYPE(e)); \
} \
catch(...) \
{ \
wrong_exception = true; \
} \
if(wrong_exception) \
{ \
Assert::Failure("Wrong exception was thrown"); \
} \
}

template <typename ExceptionType>
class ExceptionStorage
{
public:
  static std::auto_ptr<ExceptionType> last_exception;
};

template <typename ExceptionType>
std::auto_ptr<ExceptionType> ExceptionStorage<ExceptionType>::last_exception(NULL);

template <typename ExceptionType>
inline ExceptionType& LastException()
{
  if(ExceptionStorage<ExceptionType>::last_exception.get() == NULL)
  {
    Assert::Failure("No exception was stored");
  }
  
  return *(ExceptionStorage<ExceptionType>::last_exception.get());
}

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
    AssertThrows(std::exception, objectUnderTest.LogicError());
  }
  
  Spec(CanAssertOnLastException)
  {
    AssertThrows(std::logic_error, objectUnderTest.LogicError());
    Assert::That(LastException<std::logic_error>().what(), Contains("not logical!"));
  }
  
  Spec(CanDetectWhenWrongExceptionIsThrown)
  {    
    AssertTestFails(AssertThrows(std::logic_error, objectUnderTest.RangeError()), "Wrong exception");
  }

  Spec(CanHaveSeveralExceptionAssertionsInSameSpec)
  {
    AssertThrows(std::logic_error, objectUnderTest.LogicError());
    Assert::That(LastException<std::logic_error>().what(), Contains("not logical!"));

    AssertThrows(std::range_error, objectUnderTest.RangeError());
    Assert::That(LastException<std::range_error>().what(), Contains("range error!"));
  }
};


