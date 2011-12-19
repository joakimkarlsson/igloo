
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

    void ContextRunStarting(const std::string& contextName, const MetaData& metadata)
    {
      std::stringstream stm;
      stm << "ContextRunStarting called for context '" << contextName << "'" << std::endl;
      stm << "ContextRunStarting called with metadata '" << metadata.GetMetaData("metadata name") << "'" << std::endl;
      callLog += stm.str();
    }

    void ContextRunEnded(const std::string& contextName, const MetaData& metadata)
    {
      std::stringstream stm;
      stm << "ContextRunEnded called for context '" << contextName << "'" << std::endl;
      stm << "ContextRunEnded called with metadata '" << metadata.GetMetaData("metadata name") << "'" << std::endl;
      callLog += stm.str();
    }

    std::string callLog;
};

class FakeContextRunner : public BaseContextRunner
{
  public:
    FakeContextRunner() : BaseContextRunner("ContextName"), metadata("fake metadata") {}
    virtual void RunContext(TestResults& results) const
    {
      TestResultFactory factory(ContextName(), "SpecName");
      results.AddResult(factory.CreateSuccessful());
    }

    virtual const std::string& GetMetaData(const std::string&) const
    {
      return metadata;
    }

  private:
    std::string metadata;

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

  Spec(a_callback_is_made_when_context_run_starts)
  {
    runner->Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("ContextRunStarting called for context 'ContextName'"));
  }

  Spec(a_callback_is_made_when_context_run_ends)
  {
    runner->Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("ContextRunEnded called for context 'ContextName'"));
  }

  Spec(metadata_can_be_accessed_from_callback_when_context_run_is_starting)
  {
    runner->Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("ContextRunStarting called with metadata 'fake metadata'"));
  }

  Spec(metadata_can_be_accessed_from_callback_when_context_run_is_ending)
  {
    runner->Run(contextRunners);

    AssertThat(listener.callLog, Has().Exactly(1).EqualTo("ContextRunEnded called with metadata 'fake metadata'"));
  }
};
