
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include <memory>

using namespace igloo;

Context(DefaultTestResultsOutput_EmptyTestRun)
{
  std::auto_ptr<DefaultTestResultsOutput> output;
  std::stringstream resulting_stream;
  TestResults results;

  void SetUp()
  {
    output = std::auto_ptr<DefaultTestResultsOutput>(new DefaultTestResultsOutput(resulting_stream));
  }

  Spec(OutputsASummaryLineWithNoTests)
  {
    output->PrintResult(results);

    Assert::That(resulting_stream.str(), Is().StartingWith("Test run complete. 0 tests run, 0 succeeded, 0 failed."));
  }

  Context(DefaultTestResultsOutput_OneFailedTest)
  {
    void SetUp()
    {
      testResults().push_back(TestResult("A context name", "A spec name", false, "The error message"));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(DisplaysOneFailedTestOnSummary)
    {
      Assert::That(resulting_output(), Has().Exactly(1).StartingWith("Test run complete. 1 tests run, 0 succeeded, 1 failed."));
    }

    Spec(DisplaysErrorTextForFailedTestCorrectly)
    {
      Assert::That(resulting_output(), Is().StartingWith("A context name::A spec name failed:\nThe error message"));
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
