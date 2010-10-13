
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_EXCEPTIONS_H
#define IGLOO_EXCEPTIONS_H

#include <igloo/core/assert.h>

namespace igloo {
  
  template <typename ExceptionType, typename TypeUnderTest, typename MethodUnderTest>
  ExceptionType Thrown(TypeUnderTest& objectUnderTest, MethodUnderTest method)
  {
    bool unknown_exception_caught = false;
    
    try 
    {
      (objectUnderTest.*method)();
    }
    catch (const ExceptionType& e) 
    {
      return e;
    }
    catch(...)
    {
      unknown_exception_caught = true;
    }
    
    std::string error_msg = unknown_exception_caught ? "An exception of the wrong type was thrown" : "No exception thrown";
    Assert::Failure(error_msg);
    throw;
  }
  
}


#endif


