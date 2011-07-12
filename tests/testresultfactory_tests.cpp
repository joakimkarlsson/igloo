
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;


Context(An_assertion_without_file_and_linenumber_information)
{
  AssertionException exception;
  TestResultFactory factory;

  An_assertion_without_file_and_linenumber_information() 
    : exception("An error message")
      ,factory("A context name", "A spec name") 
  {}

  Spec(Created_TestResult_should_have_no_linenumber)
  {
    TestResult result = factory.CreateFromException(exception);

    Assert::That(result.HasLineNumber(), IsFalse());
    Assert::That(result.LineNumber(), Equals(0u));
  }

  Spec(Created_TestResult_should_have_no_file_information)
  {
    TestResult result = factory.CreateFromException(exception);

    Assert::That(result.HasFilename(), IsFalse());
    Assert::That(result.Filename(), IsEmpty()); 
  }

};
