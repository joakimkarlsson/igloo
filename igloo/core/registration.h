
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_REGISTRATION_H
#define IGLOO_REGISTRATION_H

#define IGLOO_PRIVATE_GENERATE_CONTEXTREGISTRAR(contextName, baseContextName) \
  struct contextName; \
  struct ContextRegistrar_##contextName \
  { \
    ContextRegistrar_##contextName() \
    { \
      igloo::TestRunner::RegisterContext<igloo::ContextRunner<baseContextName, contextName> >(#contextName); \
    } \
  } contextName##_IglooRegistrar;

#define IGLOO_CONTEXT_REGISTRATION(contextName) \
  IGLOO_PRIVATE_GENERATE_CONTEXTREGISTRAR(contextName, void); \
  struct contextName : public ContextProvider<contextName, IGLOO_CURRENT_CONTEXT>

#define IGLOO_SUBCONTEXT_REGISTRATION(contextName, baseContextName) \
  IGLOO_PRIVATE_GENERATE_CONTEXTREGISTRAR(contextName, baseContextName); \
  struct contextName : public baseContextName

#define IGLOO_SPEC_REGISTRATION(specName) \
  struct SpecRegistrar_##specName \
  { \
    SpecRegistrar_##specName() \
    { \
	  ContextRegistry<IGLOO_CURRENT_CONTEXT>::RegisterSpec(#specName, &IGLOO_CURRENT_CONTEXT::specName); \
    } \
  } SpecRegistrar_##specName; \
  virtual void specName()

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
