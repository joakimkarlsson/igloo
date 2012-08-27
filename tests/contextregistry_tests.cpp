
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

using namespace igloo;

Context(a_context_runner)
{
  struct ContextWithContextSetUpAndTearDown : public ContextProvider<ContextWithContextSetUpAndTearDown, ContextWithAttribute<void> >
  {
    static void SetUpContext()
    {
      std::stringstream stm;
      stm << "SetUpContext called." << std::endl;
      callLog() += stm.str();
    }

    static void TearDownContext()
    {
      std::stringstream stm;
      stm << "TearDownContext called." << std::endl;
      callLog() += stm.str();
    }

    static std::string& callLog()
    {
      static std::string callLog;
      return callLog;
    }
  };

  void SetUp()
  {
    ContextWithContextSetUpAndTearDown::callLog() = "";

    NullTestListener testListener;
    TestResults testResults;
    ContextRegistry<ContextWithContextSetUpAndTearDown>::Run<ContextWithContextSetUpAndTearDown>("ContextWithContextSetUpAndTearDown", testResults, testListener);
  }

  Spec(context_setup_should_be_called_first)
  {
    AssertThat(ContextWithContextSetUpAndTearDown::callLog(), StartsWith("SetUpContext called."));
  }

  Spec(context_tear_down_should_be_called_last)
  {
    AssertThat(ContextWithContextSetUpAndTearDown::callLog(), EndsWith("TearDownContext called.\n"));
  }
};

Context(a_context_that_throws_an_unknown_exception_during_test_run)
{
  struct ContextThatFailsDuringSetUp : public ContextProvider<ContextThatFailsDuringSetUp, ContextWithAttribute<void> >
  {
    void SetUp()
    {
      throw "unknown error";
    }

    Spec(a_spec)
    {
    }
  } failing_context;

  void SetUp()
  {
    failing_context.SetName("ContextThatFailsDuringSetUp");
  }

  Spec(exception_should_be_stored_in_test_result)
  {
    ContextRegistry<ContextThatFailsDuringSetUp>::CallSpec(failing_context, "a_spec", &ContextThatFailsDuringSetUp::a_spec, results);
    Assert::That(results.FailedTests(), Has().Exactly(1).EqualTo(FailedTestResult("ContextThatFailsDuringSetUp", "a_spec", "Caught unknown exception")));
  }

  TestResults results;
};
