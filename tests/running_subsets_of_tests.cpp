
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include "fakes/fake_context_runner.h"
#include "fakes/null_test_results_output.h"

using namespace igloo;

Context(TestRunner_)
{
  TestRunner_() :
    contextRunner_Only("with_only"),
    contextRunner("without_only")
  {}

  void SetUp()
  {
    contextRunner_Only.MarkAsOnly();
    runner = std::auto_ptr<TestRunner>(new TestRunner(nullOutput));
  }

  Context(no_only_specified)
  {
    void SetUp()
    {
      Parent().contextRunners.push_back(&(Parent().contextRunner));
    }

    Spec(should_run_the_context)
    {
      Parent().RunTests();
      Assert::That(Parent().contextRunner.callLog, Has().Exactly(1).EqualTo("RunContext for 'without_only' called"));
    }

    Context(one_only_specified)
    {
      void SetUp()
      {
        Parent().Parent().contextRunners.push_back(&(Parent().Parent().contextRunner_Only));
      }

      Spec(should_run_context_marked_only)
      {
        Parent().Parent().RunTests();
        Assert::That(Parent().Parent().contextRunner_Only.callLog, Has().Exactly(1).EqualTo("RunContext for 'with_only' called"));
        Assert::That(Parent().Parent().contextRunner.callLog, Has().None().EqualTo("RunContext 'without_only' called"));
      }
    };
  };

  void RunTests()
  {
    runner->Run(contextRunners);
  }

  
  fakes::FakeContextRunner contextRunner_Only;
  fakes::FakeContextRunner contextRunner;
  std::auto_ptr<TestRunner> runner;
  fakes::NullTestResultsOutput nullOutput;
  TestRunner::ContextRunners contextRunners;
};
