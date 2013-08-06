
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include "fakes/fake_context_runner.h"
#include "fakes/null_test_results_output.h"
#include "fakes/fake_test_listener.h"

using namespace igloo;

Context(registering_a_test_listener)
{
  fakes::NullTestResultsOutput nullOutput;
  std::auto_ptr<TestRunner> runner;
  TestRunner::ContextRunners contextRunners;
  fakes::FakeTestListener listener;
  fakes::FakeContextRunner contextRunner;
  
  registering_a_test_listener() : contextRunner("contextName", "file1", 44) {}

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

Context(a_registered_context)
{
  struct ContextToRun : public ContextProvider<ContextToRun, ContextWithAttribute<void>, void, false, false >
  {
    ContextAttribute("attribute name", "attribute value")

    Spec(SucceedingSpec)
    {
      Assert::That(true);
    }

    Spec(FailingSpec)
    {
      Assert::That(false);
    }
  };

  void SetUp()
  {
    ContextRegistry<ContextToRun>::RegisterSpec("SucceedingSpec", &ContextToRun::SucceedingSpec);
    ContextRegistry<ContextToRun>::RegisterSpec("FailingSpec", &ContextToRun::FailingSpec);
    ContextRegistry<ContextToRun>::Run<ContextToRun>("ContextToRun", testResults, testListener);
  }

  void TearDown()
  {
    ContextRegistry<ContextToRun>::ClearRegisteredSpecs();
  }

  Spec(ContextRunStarting_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("ContextRunStarting called for context 'ContextToRun'"));
  }

  Spec(ContextRunStarting_is_called_with_attribute)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("ContextRunStarting called with attribute 'attribute value'"));
  }

  Spec(ContextRunEnded_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("ContextRunEnded called for context 'ContextToRun'"));
  }

  Spec(ContextRunEnded_is_called_with_attribute)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("ContextRunEnded called with attribute 'attribute value'"));
  }

  Spec(SpecRunStarting_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("SpecRunStarting called for context 'ContextToRun' and spec 'SucceedingSpec'"));
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("SpecRunStarting called for context 'ContextToRun' and spec 'FailingSpec'"));
  }

  Spec(SpecSucceeded_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("SpecSucceeded called for context 'ContextToRun' and spec 'SucceedingSpec'"));
  }

  Spec(SpecFailed_is_called)
  {
    AssertThat(testListener.callLog, Has().Exactly(1).EqualTo("SpecFailed called for context 'ContextToRun' and spec 'FailingSpec'"));
  }

  fakes::FakeTestListener testListener;
  TestResults testResults;
};
