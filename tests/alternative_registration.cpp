
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <igloo/igloo_alt.h>
using namespace igloo;

Describe(An_entity)
{
  bool its_true; 

  An_entity() : its_true(true) {}

  It(should_do_something)
  {
    Assert::That(its_true, IsTrue());
  }

  Describe(A_more_detailed_description)
  {
    A_more_detailed_description() 
    {
      Parent().its_true = false;
    }
    
    It(should_do_something)
    {
      Assert::That(Parent().its_true, IsFalse());
    }

    Describe(even_more_nesting_with_direct_access_to_root)
    {
      void SetUp()
      {
        Root().its_true = true;
      }

      It(should_have_direct_access_to_the_root_context)
      {
        Assert::That(Root().its_true, IsTrue());
      }
    };
  };
};

When(A_scenario_occurs)
{
  bool some_state;

  A_scenario_occurs() : some_state(true) {}

  Then(Should_be_in_a_state)
  {
    Assert::That(some_state, IsTrue());
  }

  When(A_more_detailed_variant_occurs)
  {
    A_more_detailed_variant_occurs() 
    {
      Parent().some_state = false;
    }

    Then(Should_be_in_a_state)
    {
      Assert::That(Parent().some_state, IsFalse());
    }
  };
};
