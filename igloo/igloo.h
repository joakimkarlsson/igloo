#ifndef IGLOO_IGLOO_H
#define IGLOO_IGLOO_H

// Cuts build time by 40% on my Visual C++
#define _HAS_TR1 0

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stack>
#include <list>

#include "igloo/core/stringize.h"
#include "igloo/constraints/constraints.h"
#include "igloo/fluent/fluent.h"

#include "igloo/core/assertionexception.h"
#include "igloo/core/testfixture.h" 
#include "igloo/core/testfixturerunner.h"
#include "igloo/core/testrunner.h"
#include "igloo/core/assert.h"                

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
