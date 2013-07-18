
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include "fakes/fake_context_runner.h"
#include "fakes/null_test_results_output.h"
#include "fakes/fake_test_listener.h"

using namespace igloo;

Context(context_with_ignored_specs)
{
  struct ContextToRun : public ContextProvider<ContextToRun, ContextWithAttribute<void>, void, false, false >
  {
    Spec(SpecToRun)
    {
      spec_to_run_called_ = true;
    }

    Spec_Skip(SpecToSkip)
    {
      spec_to_skip_called_ = true;
    }

    public:
      static bool spec_to_run_called_;
      static bool spec_to_skip_called_;
  };

  void SetUp()
  {
    ContextToRun::spec_to_run_called_ = false;
    ContextToRun::spec_to_skip_called_ = false;
    ContextRegistry<ContextToRun>::RegisterSpec("SpecToRun", &ContextToRun::SpecToRun);
    ContextRegistry<ContextToRun>::RegisterSpec("SpecToSkip", &ContextToRun::SpecToSkip, true);
    ContextRegistry<ContextToRun>::Run<ContextToRun>("ContextToRun", testResults, testListener);
  }

  void TearDown()
  {
    ContextRegistry<ContextToRun>::ClearRegisteredSpecs();
  }

  Spec(calls_spec_to_be_run)
  {
    AssertThat(ContextToRun::spec_to_run_called_, Equals(true));
  }

  Spec(does_not_call_spec_to_be_skipped)
  {
    AssertThat(ContextToRun::spec_to_skip_called_, Equals(false));
  }

  fakes::FakeTestListener testListener;
  TestResults testResults;
};

bool context_with_ignored_specs::ContextToRun::spec_to_run_called_;
bool context_with_ignored_specs::ContextToRun::spec_to_skip_called_;
