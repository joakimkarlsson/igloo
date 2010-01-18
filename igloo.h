#ifndef IGLOO_IGLOO_H
#define IGLOO_IGLOO_H

#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "syntax.h"
#include "assertionexception.h"
#include "testfixture.h"
#include "testrunner.h"
#include "assert.h"                

#include "constraints/equalsconstraint.h"
#include "constraints/isgreaterthanconstraint.h"
#include "constraints/islessthanconstraint.h"       
#include "constraints/containsconstraint.h"
#include "constraints/haslengthconstraint.h"
#include "constraints/startswithconstraint.h"
#include "constraints/endswithconstraint.h"

#define IGLOO_PP_CAT(a, b) IGLOO_PP_CAT_I(a, b)
#define IGLOO_PP_CAT_I(a, b) a ## b

#define TestFixture(fixture) \
struct fixture; \
	const int IGLOO_PP_CAT(IGLOO_FIRST_METHOD_SLOT_, fixture) = __COUNTER__; \
int fixture##_dummy = igloo::TestRunner::RegisterTestFixture( #fixture , new igloo::TestFixture<fixture>()); \
struct fixture : public igloo::TestFixture<fixture>
         
#define TestMethod(method) \
struct TestMethodRegistrar##method \
{ \
  TestMethodRegistrar##method() \
  { \
    IGLOO_FIXTURE_TYPE::RegisterTestMethod(#method, &IGLOO_FIXTURE_TYPE::method); \
  } \
} method##Registrar; \
\
void method()

#endif
