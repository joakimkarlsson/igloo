
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_ALTERNATIVEREGISTRATIONALIASES_H
#define IGLOO_ALTERNATIVEREGISTRATIONALIASES_H

#include <igloo/core/registration.h>

// Spec aliases
#define Describe(contextName) \
IGLOO_CONTEXT_REGISTRATION(contextName)

#define It(specName) \
IGLOO_SPEC_REGISTRATION(specName)  

// Behavior aliases
#define When(contextName) \
IGLOO_CONTEXT_REGISTRATION(contextName)

#endif
