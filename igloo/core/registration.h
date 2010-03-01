
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_REGISTRATION_H
#define IGLOO_REGISTRATION_H

#define Context(context) \
struct context; \
struct ContextRegistrar_##context \
{ \
  ContextRegistrar_##context() \
  { \
    igloo::TestRunner::RegisterTestFixture<igloo::TestFixtureRunner<void, context> >(#context); \
  } \
} context##_IglooRegistrar; \
struct context : public ContextProvider<context, IGLOO_CURRENT_CONTEXT>

#define SubContext(context, baseContext) \
struct context; \
struct ContextRegistrar_##context \
{ \
ContextRegistrar_##context() \
{ \
igloo::TestRunner::RegisterTestFixture<igloo::TestFixtureRunner<baseContext, context> >(#context); \
} \
} context##_IglooRegistrar; \
struct context : public baseContext

#define Spec(spec) \
struct SpecRegistrar_##spec \
{ \
  SpecRegistrar_##spec() \
  { \
    BaseFixture<IGLOO_CURRENT_CONTEXT>::RegisterTestMethod(#spec, &IGLOO_CURRENT_CONTEXT::spec); \
  } \
} SpecRegistrar_##spec; \
virtual void spec()

#endif
