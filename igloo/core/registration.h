
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
    igloo::TestRunner::RegisterContext<igloo::ContextRunner<void, context> >(#context); \
  } \
} context##_IglooRegistrar; \
struct context : public ContextProvider<context, IGLOO_CURRENT_CONTEXT>

#define SubContext(context, baseContext) \
struct context; \
struct ContextRegistrar_##context \
{ \
ContextRegistrar_##context() \
{ \
igloo::TestRunner::RegisterContext<igloo::ContextRunner<baseContext, context> >(#context); \
} \
} context##_IglooRegistrar; \
struct context : public baseContext

#define Spec(spec) \
struct SpecRegistrar_##spec \
{ \
  SpecRegistrar_##spec() \
  { \
    ContextRegistry<IGLOO_CURRENT_CONTEXT>::RegisterSpec(#spec, &IGLOO_CURRENT_CONTEXT::spec); \
  } \
} SpecRegistrar_##spec; \
virtual void spec()


#define TestFixture(context) \
struct context; \
struct ContextRegistrar_##context \
{ \
ContextRegistrar_##context() \
{ \
igloo::TestRunner::RegisterContext<igloo::ContextRunner<void, context> >(#context); \
} \
} context##_IglooRegistrar; \
struct context : public ContextProvider<context, IGLOO_CURRENT_CONTEXT>

#define DerivedFixture(context, baseContext) \
struct context; \
struct ContextRegistrar_##context \
{ \
ContextRegistrar_##context() \
{ \
igloo::TestRunner::RegisterContext<igloo::ContextRunner<baseContext, context> >(#context); \
} \
} context##_IglooRegistrar; \
struct context : public baseContext

#define TestMethod(spec) \
struct SpecRegistrar_##spec \
{ \
SpecRegistrar_##spec() \
{ \
ContextRegistry<IGLOO_CURRENT_CONTEXT>::RegisterSpec(#spec, &IGLOO_CURRENT_CONTEXT::spec); \
} \
} SpecRegistrar_##spec; \
virtual void spec()

#endif
