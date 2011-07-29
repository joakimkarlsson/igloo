
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

using namespace igloo;

class NullTestResultsOutput : public TestResultsOutput
{
    public:
      void PrintResult(const TestResults&, std::ostream&) const 
      {
      }
};

class FakeTestListener : public TestListener
{
  public:
    void TestRunStarting()
    {
      callLog += "TestRunStarting\n";
    }

    std::string callLog;
};

Context(registering_a_test_listener)
{
  Spec(it_calls_back_when_test_run_starts)
  {
    NullTestResultsOutput nullOutput;
    TestRunner runner(nullOutput);
    TestRunner::ContextRunners contextRunners;
    FakeTestListener listener;
    runner.AddListener(&listener);

    runner.Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("TestRunStarting"));
  }
};
