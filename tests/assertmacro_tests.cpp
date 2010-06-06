
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

Context(AssertMacro)
{
  
  Spec(CanBeCalledInBothForms)
  {
    AssertThat(10, Is().LessThan(20).And().GreaterThan(5).And().EqualTo(6+4));
    AssertThat(10, IsLessThan(20) && IsGreaterThan(5) && Equals(5+5));
  };
  
  Spec(DisplaysFileAndLineNumberForErrors)
  {
    const char* file_name = "A file name";
    int line_number = 453;

    std::ostringstream expected_error_message;
    
    expected_error_message << file_name << "(" << line_number << "): Assertion failed" << std::endl;  

    AssertTestFails(Assert::That(5, Equals(3), file_name, line_number), expected_error_message.str());
  }

  Spec(DisplaysFileAndLineNumberForFluentForm)
  {
    const char* file_name = "A file name";
    int line_number = 453;

    std::ostringstream expected_error_message;
    
    expected_error_message << file_name << "(" << line_number << "): Assertion failed" << std::endl;  

    AssertTestFails(Assert::That(5, Is().EqualTo(3), file_name, line_number), expected_error_message.str());
  }

};

