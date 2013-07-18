
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTS_FAKES_FAKE_TEST_LISTENER_H
#define IGLOO_TESTS_FAKES_FAKE_TEST_LISTENER_H

namespace igloo { namespace fakes {

  class FakeTestListener : public TestListener
  {
    public:
      void TestRunStarting()
      {
        callLog += "TestRunStarting\n";
      }

      void TestRunEnded(const TestResults& results)
      {
        std::stringstream stm;
        stm << "TestRunEnded called with " << results.NumberOfTestsRun() << " tests run" << std::endl;
        callLog += stm.str();
      }

      void ContextRunStarting(const ContextBase& context)
      {
        std::stringstream stm;
        stm << "ContextRunStarting called for context '" << context.Name() << "'" << std::endl;
        stm << "ContextRunStarting called with attribute '" << context.GetAttribute("attribute name") << "'" << std::endl;
        callLog += stm.str();
      }

      void ContextRunEnded(const ContextBase& context)
      {
        std::stringstream stm;
        stm << "ContextRunEnded called for context '" << context.Name() << "'" << std::endl;
        stm << "ContextRunEnded called with attribute '" << context.GetAttribute("attribute name") << "'" << std::endl;
        callLog += stm.str();
      }

      void SpecRunStarting(const ContextBase& context, const std::string& name)
      {
        std::stringstream stm;
        stm << "SpecRunStarting called for context '" << context.Name() << "' and spec '" << name << "'" << std::endl;
        callLog += stm.str();
      }

      void SpecSucceeded(const ContextBase& context, const std::string& name)
      {
        std::stringstream stm;
        stm << "SpecSucceeded called for context '" << context.Name() << "' and spec '" << name << "'" << std::endl;
        callLog += stm.str();
      }

      void SpecFailed(const ContextBase& context, const std::string& name)
      {
        std::stringstream stm;
        stm << "SpecFailed called for context '" << context.Name() << "' and spec '" << name << "'" << std::endl;
        callLog += stm.str();
      }

      std::string callLog;
  };

}}
#endif
