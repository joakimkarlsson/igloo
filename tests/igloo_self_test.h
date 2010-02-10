#ifndef IGLOO_SELF_TEST_H
#define IGLOO_SELF_TEST_H

#include "igloo/igloo.h"

#define AssertTestFails(assertion, expected_error_text) \
  std::string IGLOO_INTERNAL_expected_error = "Test did not fail"; \
  try \
  { \
    assertion; \
  }  \
  catch(const AssertionException& e)  \
  {  \
  IGLOO_INTERNAL_expected_error = e.GetMessage();  \
  }  \
  Assert::That(IGLOO_INTERNAL_expected_error, Is().Containing(expected_error_text));

#endif
