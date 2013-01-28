// 
//  IglooHelper.hpp
//  
//  Created to extend igloo functionality
//
#ifndef IGLOOHELPER_HPP_ZB9KTXAQ
#define IGLOOHELPER_HPP_ZB9KTXAQ

#include <igloo/igloo.h>

/*
	Checks that an exception was thrown, doesn't care what.
	@param block A block of code that should throw an exception
	
	For use inside an Igloo Spec
*/
#define ShouldThrowError(block) {\
	bool threw_error = false;\
	try block \
	catch(...) {\
		threw_error = true; \
	}\
	Assert::That(threw_error, Equals(true));\
}

/*
	Checks that an exception was thrown, with a given "what" value.
	@param block A block of code that should throw an exception
	@param expected_what  A string to compare the what field of the error with.
	
	For use inside an Igloo Spec.
*/
#define ShouldThrowWhatError(block, expected_what) {\
	bool threw_error = false;\
	try block \
	catch(std::exception& e) {\
		Assert::That(e.what(), Is().EqualTo(expected_what)); \
		threw_error = true; \
	}\
	Assert::That(threw_error, Is().EqualTo(true));\
}

#endif /* end of include guard: IGLOOHELPER_HPP_ZB9KTXAQ */
