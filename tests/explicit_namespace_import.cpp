
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <igloo/igloo_alt.h>

//
// Ensure that we can use igloo without explicitly importing all of the 'igloo'
// namespace.
//

using snowhouse::Equals;

Describe(can_be_used_without_importing_whole_namespace)
{
    It(does_a_silly_assert)
    {
        AssertThat(5, Equals(5));
    }
};
