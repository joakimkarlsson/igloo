
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_REGISTRATION_H
#define IGLOO_REGISTRATION_H

#define TestFixture(fixture) \
struct fixture; \
struct TestFixtureRegistrar##fixture \
{ \
TestFixtureRegistrar##fixture() \
{ \
igloo::TestRunner::RegisterTestFixture<igloo::TestFixtureRunner<void, fixture> >(#fixture); \
} \
} fixture##IglooRegistrar; \
struct fixture : public igloo::BaseFixture<fixture>

#define DerivedFixture(fixture, basefixture) \
struct fixture; \
struct TestFixtureRegistrar##fixture \
{ \
TestFixtureRegistrar##fixture() \
{ \
igloo::TestRunner::RegisterTestFixture<igloo::TestFixtureRunner<basefixture, fixture> >(#fixture); \
} \
} fixture##IglooRegistrar; \
struct fixture : public basefixture

#define TestMethod(method) \
struct TestMethodRegistrar##method \
{ \
TestMethodRegistrar##method() \
{ \
BaseFixture<IGLOO_FIXTURE_TYPE>::RegisterTestMethod(#method, &IGLOO_FIXTURE_TYPE::method); \
} \
} method##Registrar; \
\
virtual void method()

template <typename T>
T* CreateIglooContext()
{
  return new T();
}

template <typename InnerContext, typename OuterContext>
struct ContextBridge : public igloo::TestFixtureBase
{
  typedef InnerContext IGLOO_CURRENT_CONTEXT;
  typedef InnerContext IGLOO_OUTER_CONTEXT;
  
  virtual OuterContext& Parent()
  {
    if(m_outerContext.get() == 0)
    {
      m_outerContext = std::auto_ptr<OuterContext>(CreateIglooContext<OuterContext>());
    }
    return *(m_outerContext.get());
  }
  
  virtual void IglooFrameworkSetUp()
  {
    Parent().IglooFrameworkSetUp();
    SetUp();
  }

  virtual void IglooFrameworkTearDown()
  {
    TearDown();
    Parent().IglooFrameworkTearDown();
  }
  
  std::auto_ptr<OuterContext> m_outerContext;
};

template <typename InnerContext, typename OuterContext>
struct OuterContextSelector
{
  typedef ContextBridge<InnerContext, OuterContext> SelectedContext;
};

template <typename InnerContext>
struct OuterContextSelector<InnerContext, void>
{
  typedef ContextBridge<InnerContext, igloo::TestFixtureBase > SelectedContext;
};

#define Context(context) \
struct context; \
struct ContextRegistrar_##context \
{ \
  ContextRegistrar_##context() \
  { \
    igloo::TestRunner::RegisterTestFixture<igloo::TestFixtureRunner<void, context> >(#context); \
  } \
} context##_IglooRegistrar; \
struct context : public ContextBridge<context, IGLOO_CURRENT_CONTEXT>

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
