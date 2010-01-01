#ifndef _IGLOO_HPP
#define _IGLOO_HPP

#include <iostream>
#include <map>
#include <vector>

#include "syntax.h"
#include "assertionexception.hpp"
#include "testfixture.hpp"
#include "testrunner.hpp"                                           
#include "assert.h"

#define IGLOO_PP_CAT(a, b) IGLOO_PP_CAT_I(a, b)
#define IGLOO_PP_CAT_I(a, b) a ## b

#define TestFixture(fixture) \
class fixture; \
   int fixture##_dummy = igloo::TestRunner::RegisterTestFixture( #fixture , new igloo::TestFixture<fixture>()); \
class fixture : public igloo::TestFixture<fixture>            

#define TestMethod(fixture, method) \
bool IGLOO_PP_CAT(GetTest, __COUNTER__)(std::map<std::string, void (fixture::*)() >& tests) \
{ \
   tests[#method] = &fixture::method; \
   return true; \
} \
void method()

#endif
