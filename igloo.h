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

#define IGLOO_PP_CAT(a, b) IGLOO_PP_CAT_I(a, b)
#define IGLOO_PP_CAT_I(a, b) a ## b

#define TestFixture(fixture) \
struct fixture; \
int fixture##_dummy = igloo::TestRunner::RegisterTestFixture( #fixture , new igloo::TestFixture<fixture>()); \
struct fixture : public igloo::TestFixture<fixture>

#define TestMethod(method) \
bool IGLOO_PP_CAT(GetTest, __COUNTER__)(std::map<std::string, void (IGLOO_FIXTURE_TYPE::*)() >& tests) \
{ \
   tests[#method] = &IGLOO_FIXTURE_TYPE::method; \
   return true; \
} \
void method()

#endif
