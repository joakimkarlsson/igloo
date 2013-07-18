#ifndef _IGLOO_TESTS_FAKES_NULL_TEST_RESULTS_OUTPUT_H
#define _IGLOO_TESTS_FAKES_NULL_TEST_RESULTS_OUTPUT_H

//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace igloo { namespace fakes {
  class NullTestResultsOutput : public TestResultsOutput
  {
    public:
      void PrintResult(const TestResults&) const 
      {
      }
  };

}}

#endif
