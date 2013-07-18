//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include <memory>

using namespace igloo;

Context(ColoredConsoleTestResultsOutput_EmptyTestRun)
{
  std::auto_ptr<ColoredConsoleTestResultsOutput> output;
  std::stringstream resulting_stream;
  TestResults results;

  void SetUp()
  {
    output = std::auto_ptr<ColoredConsoleTestResultsOutput>(new ColoredConsoleTestResultsOutput(resulting_stream));
  }

  Spec(OutputsASummaryLineWithNoTests)
  {
    output->PrintResult(results);

    Assert::That(resulting_stream.str(), Is().StartingWith(std::string(PASSED_OUTPUT_COLOR) + std::string("Test run complete. 0 tests run:\n0 succeeded\n0 failed") + std::string(DEFAULT_OUTPUT_COLOR)));
  }

  Context(ColoredConsoleTestResultsOutput_OneFailedTest_with_no_info_about_location_of_error)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A spec name", "The error message"));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(DisplaysOneTestsRunOnSummary)
    {
    	Assert::That(resulting_output(), Has().Exactly(1).StartingWith(std::string(FAILED_OUTPUT_COLOR) + std::string("Test run complete. 1 tests run:")));
    }

    Spec(DisplaysZeroSuccessfulTestsOnSummary)
	{
		Assert::That(resulting_output(), Has().Exactly(1).StartingWith("0 succeeded"));
	}

    Spec(DisplaysOneFailedTestOnSummary)
	{
		Assert::That(resulting_output(), Has().Exactly(1).StartingWith(std::string("1 failed") + std::string(DEFAULT_OUTPUT_COLOR)));
	}

    Spec(DisplaysErrorTextForFailedTestCorrectly)
    {
      Assert::That(resulting_output(), Is().StartingWith(std::string(FAILED_OUTPUT_COLOR) + std::string("A context name::A spec name failed:\nThe error message") + std::string(DEFAULT_OUTPUT_COLOR)));
    }

    TestResults& testResults() 
    {
      return Parent().results;
    }
    
    std::string resulting_output() 
    {
      return Parent().resulting_stream.str();
    }
  };

  Context(ColoredConsoleTestResultsOutput_one_failed_test_with_information_about_origin_of_assertion)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A spec name", "The error message", "filewithfailure.cpp", 342));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(DisplaysOneTestsRunOnSummary)
	{
    	Assert::That(resulting_output(), Has().Exactly(1).StartingWith(std::string(FAILED_OUTPUT_COLOR) + std::string("Test run complete. 1 tests run:")));
	}

	Spec(DisplaysZeroSuccessfulTestsOnSummary)
	{
		Assert::That(resulting_output(), Has().Exactly(1).StartingWith("0 succeeded"));
	}

	Spec(DisplaysOneFailedTestOnSummary)
	{
		Assert::That(resulting_output(), Has().Exactly(1).StartingWith(std::string("1 failed") + std::string(DEFAULT_OUTPUT_COLOR)));
	}

    Spec(DisplaysErrorTextForFailedTestCorrectly)
    {
      Assert::That(resulting_output(), Is().StartingWith(std::string(FAILED_OUTPUT_COLOR) + std::string("A context name::A spec name failed:\nfilewithfailure.cpp(342): Assertion failed.\nThe error message") + std::string(DEFAULT_OUTPUT_COLOR)));
    }

    TestResults& testResults()
    {
      return Parent().results;
    }

    std::string resulting_output()
    {
      return Parent().resulting_stream.str();
    }
  };
};
