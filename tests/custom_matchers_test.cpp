
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include <igloo/core/stringizers.h>

using namespace igloo;

Context(CustomMatchers)
{
  struct IsEvenNumber
  {
    bool Matches(const int actual) const
    {
      return (actual % 2) == 0; 
    }
  };

  Spec(CanHandleCustomMatcher)
  {
    Assert::That(2, Fulfills(IsEvenNumber()));
  }
};
