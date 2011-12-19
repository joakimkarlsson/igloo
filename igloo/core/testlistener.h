
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTLISTENER_H
#define IGLOO_TESTLISTENER_H

namespace igloo {

  class TestListener
  {
    public:
      virtual void TestRunStarting() = 0;
      virtual void TestRunEnded(const TestResults& results) = 0;
      virtual void ContextRunStarting(const std::string& contextName, const MetaData& metadata) = 0;
      virtual void ContextRunEnded(const std::string& contextName, const MetaData& metadata) = 0;
  };
}

#endif
