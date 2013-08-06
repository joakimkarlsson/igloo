
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
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
    contextRunner("without_only", "file1", 12),
    contextRunner_Only("with_only", "file2", 13),
    contextRunner_Skip("with_skip", "file3", 14)
  {}

  void SetUp()
  {
    contextRunner_Only.MarkAsOnly();
    contextRunner_Skip.MarkAsSkip();
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
      Assert::That(Parent().contextRunner.callLog, Has().Exactly(1).EqualTo("RunContext called"));
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
        Assert::That(Parent().Parent().contextRunner_Only.callLog, Has().Exactly(1).EqualTo("RunContext called"));
        Assert::That(Parent().Parent().contextRunner.callLog, Has().None().EqualTo("RunContext called"));
      }
    };

    Context(one_skip_specified)
    {
      void SetUp()
      {
        Parent().Parent().contextRunners.push_back(&(Parent().Parent().contextRunner_Skip));
      }

      Spec(should_not_run_context_marked_skip)
      {
        Parent().Parent().RunTests();
        Assert::That(Parent().Parent().contextRunner_Skip.callLog, Has().None().EqualTo("RunContext called"));
        Assert::That(Parent().Parent().contextRunner.callLog, Has().Exactly(1).EqualTo("RunContext called"));
      }
    };
  };

  void RunTests()
  {
    runner->Run(contextRunners);
  }

  
  fakes::FakeContextRunner contextRunner;
  fakes::FakeContextRunner contextRunner_Only;
  fakes::FakeContextRunner contextRunner_Skip;
  std::auto_ptr<TestRunner> runner;
  fakes::NullTestResultsOutput nullOutput;
  TestRunner::ContextRunners contextRunners;
};

