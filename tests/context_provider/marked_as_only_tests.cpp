
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

using namespace igloo;

Context(marking_contexts_as_only)
{
  Context(context_marked_as_only)
  {
    struct ContextMarkedAsOnly : public ContextProvider<ContextMarkedAsOnly, ContextWithAttribute<void>, void, true, false>
    {
    };

    Spec(it_is_marked_as_only)
    {
      AssertThat(ContextMarkedAsOnly::IsContextMarkedAsOnly(), IsTrue());
    }
  };

  Context(context_not_marked_as_only)
  {
    struct ContextNotMarkedAsOnly : public ContextProvider<ContextNotMarkedAsOnly, ContextWithAttribute<void>, void, false, false>
    {
    };

    Spec(it_is_not_marked_as_only)
    {
      AssertThat(ContextNotMarkedAsOnly::IsContextMarkedAsOnly(), IsFalse());
    }
  };

  Context(context_not_marked_as_only_but_with_spec_marked_as_only)
  {
    struct ContextWithSpecMarkedAsOnly : public ContextProvider<ContextWithSpecMarkedAsOnly, ContextWithAttribute<void>, void, false, false>
    {
      void spec_marked_as_only()
      {}
    };

    void SetUp()
    {
      ContextRegistry<ContextWithSpecMarkedAsOnly>::RegisterSpec("spec_marked_as_only", &ContextWithSpecMarkedAsOnly::spec_marked_as_only, false, true);
    }

    void TearDown()
    {
      ContextRegistry<ContextWithSpecMarkedAsOnly>::ClearRegisteredSpecs();
    }

    Spec(it_is_marked_as_only)
    {
      AssertThat(ContextWithSpecMarkedAsOnly::IsContextMarkedAsOnly(), IsTrue());
    }
  };
};
