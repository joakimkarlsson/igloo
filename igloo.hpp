#ifndef _IGLOO_HPP
#define _IGLOO_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include <boost/preprocessor.hpp>
#include <memory>
#include "assertionexception.hpp"
#include "testfixture.hpp"
#include "testrunner.hpp"                                           
#include "constraints/assertions.h"


int RegisterTestFixture(std::string name, TestFixtureBase* testFixture)
{        
	TestRunner::FixtureMap[name] = testFixture; 
	return 0;
}  

#define TestFixture(fixture) \
class fixture; \
int fixture##_dummy = RegisterTestFixture( #fixture , new TestFixture<fixture>()); \
class fixture : public TestFixture<fixture>            
                     
#define TestMethod(fixture, method) \
bool BOOST_PP_CAT(GetTest, __COUNTER__)(std::map<std::string, void (fixture::*)() >& tests) \
{ \
	tests[#method] = &fixture::method; \
  return true; \
} \
void method()

#endif