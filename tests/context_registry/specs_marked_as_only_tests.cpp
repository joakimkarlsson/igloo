
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

using namespace igloo;

Context(marking_specs_as_only)
{
  struct ContextToRun : public ContextProvider<ContextToRun, ContextWithAttribute<void>, void, false, false >
  {
    void this_spec_is_marked_as_only()
    {
      std::stringstream stm;
      stm << "this_spec_is_marked_as_only" << std::endl;
      callLog() += stm.str();
    };

    void normal_spec()
    {
      std::stringstream stm;
      stm << "normal_spec" << std::endl;
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
    ContextToRun::callLog() = "";

    ContextRegistry<ContextToRun>::RegisterSpec("this_spec_is_marked_as_only", &ContextToRun::this_spec_is_marked_as_only, false, true);
    ContextRegistry<ContextToRun>::RegisterSpec("normal_spec", &ContextToRun::normal_spec, false, false);

    NullTestListener testListener;
    TestResults testResults;
    ContextRegistry<ContextToRun>::Run<ContextToRun>("ContextToRun", testResults, testListener);
  }

  void TearDown()
  {
    ContextRegistry<ContextToRun>::ClearRegisteredSpecs();
  }

  Spec(should_only_call_spec_marked_as_only)
  {
    AssertThat(ContextToRun::callLog(), Has().None().StartingWith("normal_spec"));
    AssertThat(ContextToRun::callLog(), Has().Exactly(1).StartingWith("this_spec_is_marked_as_only"));
  }

  Spec(should_tell_that_context_has_specs_marked_as_only)
  {
    AssertThat(ContextRegistry<ContextToRun>::HasSpecsMarkedAsOnly(), IsTrue());
  }
};
