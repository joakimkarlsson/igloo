
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_DEFAULTREGISTRATIONALIAS_H
#define IGLOO_DEFAULTREGISTRATIONALIAS_H

#include <igloo/core/registration.h>

// Default aliases
#define Context(contextName) \
IGLOO_CONTEXT_REGISTRATION(contextName)

#define SubContext(contextName, baseContextName) \
IGLOO_SUBCONTEXT_REGISTRATION(contextName, baseContextName)

#define Spec(specName) \
IGLOO_SPEC_REGISTRATION(specName)  

// "Classic" aliases
#define TestFixture(fixtureName) \
IGLOO_CONTEXT_REGISTRATION(fixtureName)

#define DerivedFixture(fixtureName, baseFixtureName) \
IGLOO_SUBCONTEXT_REGISTRATION(fixtureName, baseFixtureName)

#define TestMethod(methodName) \
IGLOO_SPEC_REGISTRATION(methodName)

#endif
