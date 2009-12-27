#ifndef _IGLOO_HPP
#define _IGLOO_HPP

#include <iostream>
#include <map>
#include <vector>
#include <boost/preprocessor.hpp>

#include "syntax.h"
#include "assertionexception.hpp"
#include "testfixture.hpp"
#include "testrunner.hpp"                                           
#include "assert.h"

#define TestFixture(fixture) \
class fixture; \
   int fixture##_dummy = igloo::TestRunner::RegisterTestFixture( #fixture , new igloo::TestFixture<fixture>()); \
class fixture : public igloo::TestFixture<fixture>            

#define TestMethod(fixture, method) \
bool BOOST_PP_CAT(GetTest, __COUNTER__)(std::map<std::string, void (fixture::*)() >& tests) \
{ \
   tests[#method] = &fixture::method; \
   return true; \
} \
void method()

#endif
