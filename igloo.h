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
int fixture##_dummy = igloo::TestRunner::RegisterTestFixture( #fixture , new igloo::TestFixture<fixture, IGLOO_PP_CAT(IGLOO_FIRST_METHOD_SLOT_, fixture)>()); \
struct fixture : public igloo::TestFixture<fixture, IGLOO_PP_CAT(IGLOO_FIRST_METHOD_SLOT_, fixture)>
         
template <typename FixtureType, int MethodSlotValue>                             
struct test_slot_base
{ 
	typedef FixtureType SlotFixtureType;
	const static int MethodSlot = MethodSlotValue;
};

#define TestMethod(method) \
const static int IGLOO_PP_CAT(IGLOO_METHOD_SLOT_, method) = __COUNTER__; \
template <typename IGLOO_DUMMY> \
struct test_slot<IGLOO_FIXTURE_TYPE, IGLOO_PP_CAT(IGLOO_METHOD_SLOT_, method), IGLOO_DUMMY> : public test_slot_base<IGLOO_FIXTURE_TYPE, IGLOO_PP_CAT(IGLOO_METHOD_SLOT_, method)>\
{ \
	static void reg(std::map<std::string, void (IGLOO_FIXTURE_TYPE::*)()>& tests) \
	{ \
		tests[#method] = &SlotFixtureType::method; \
		test_slot<SlotFixtureType, MethodSlot+1>::reg(tests); \
	}	\
}; \
void method()

#endif
