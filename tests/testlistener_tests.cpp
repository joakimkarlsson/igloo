
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

    void TestRunEnded(const TestResults& results)
    {
      std::stringstream stm;
      stm << "TestRunEnded called with " << results.NumberOfTestsRun() << " tests run" << std::endl;
      callLog += stm.str();
    }

    std::string callLog;
};

class FakeContextRunner : public BaseContextRunner
{
  public:
    FakeContextRunner() : BaseContextRunner("ContextName") {}
    virtual void Run(TestResults& results) const
    {
      TestResultFactory factory(ContextName(), "SpecName");
      results.AddResult(factory.CreateSuccessful());
    }
};

Context(registering_a_test_listener)
{
  NullTestResultsOutput nullOutput;
  std::auto_ptr<TestRunner> runner;
  TestRunner::ContextRunners contextRunners;
  FakeTestListener listener;
  FakeContextRunner contextRunner;

  void SetUp()
  {
    runner = std::auto_ptr<TestRunner>(new TestRunner(nullOutput));
    runner->AddListener(&listener);

    contextRunners.push_back(&contextRunner);
  }

  Spec(a_callback_is_made_when_the_test_run_starts)
  {
    runner->Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("TestRunStarting"));
  }

  Spec(a_callback_is_made_when_the_test_run_ends)
  {
    runner->Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("TestRunEnded called with 1 tests run"));
  }
};
