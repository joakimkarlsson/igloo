
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

#define Context(contextName) \
  IGLOO_PRIVATE_GENERATE_CONTEXTREGISTRAR(contextName, void); \
  struct contextName : public ContextProvider<contextName, IGLOO_CURRENT_CONTEXT>

#define SubContext(contextName, baseContextName) \
  IGLOO_PRIVATE_GENERATE_CONTEXTREGISTRAR(contextName, baseContextName); \
  struct contextName : public baseContextName

#define Spec(specName) \
  struct SpecRegistrar_##specName \
  { \
    SpecRegistrar_##specName() \
    { \
	  ContextRegistry<IGLOO_CURRENT_CONTEXT>::RegisterSpec(#specName, &IGLOO_CURRENT_CONTEXT::specName); \
    } \
  } SpecRegistrar_##specName; \
  virtual void specName()

// "Classic" aliases
#define TestFixture(fixtureName) \
  Context(fixtureName)

#define DerivedFixture(fixtureName, baseFixtureName) \
  SubContext(fixtureName, baseFixtureName)

#define TestMethod(methodName) \
  Spec(methodName)

#endif
