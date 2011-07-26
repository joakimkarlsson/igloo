
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTRESULTSOUTPUT_H
#define IGLOO_TESTRESULTSOUTPUT_H

namespace igloo {

  class TestResultsOutput
  {
    public:
      virtual void PrintResult(const TestResults& results) = 0;
  };
}

#endif 
