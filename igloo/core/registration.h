
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
void method()

#endif
