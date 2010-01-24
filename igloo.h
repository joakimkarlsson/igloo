#ifndef IGLOO_IGLOO_H
#define IGLOO_IGLOO_H

#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "syntax.h"
#include "assertionexception.h"
#include "testfixture.h" 
#include "testfixturerunner.h"
#include "testrunner.h"
#include "assert.h"                

#include "constraints/equalsconstraint.h"
#include "constraints/isgreaterthanconstraint.h"
#include "constraints/islessthanconstraint.h"       
#include "constraints/containsconstraint.h"
#include "constraints/haslengthconstraint.h"
#include "constraints/startswithconstraint.h"
#include "constraints/endswithconstraint.h"

#include "fluent/fluent.h"

#define TestFixture(fixture) \
struct fixture; \
struct TestFixtureRegistrar##fixture \
{ \
   TestFixtureRegistrar##fixture() \
   { \
     igloo::TestRunner::RegisterTestFixture<igloo::TestFixtureRunner<fixture> >(#fixture); \
   } \
} fixture##IglooRegistrar; \
struct fixture : public igloo::TestFixture<fixture>
         
#define TestMethod(method) \
struct TestMethodRegistrar##method \
{ \
  TestMethodRegistrar##method() \
  { \
    TestFixtureRunner<IGLOO_FIXTURE_TYPE>::RegisterTestMethod(#method, &IGLOO_FIXTURE_TYPE::method); \
  } \
} method##Registrar; \
\
void method()

#endif
