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
void method()

#endif
