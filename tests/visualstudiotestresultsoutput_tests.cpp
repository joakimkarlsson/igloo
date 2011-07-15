
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
#include <memory>

using namespace igloo;

class VisualStudioResultsOutput
{
  public:
    VisualStudioResultsOutput(std::ostream& output)
      : output_(output)
    {}

    void PrintResult(const TestResults& results)
    {
      output_ << "Test run complete. " << results.NumberOfTestsRun() << " tests run, " << results.NumberOfSucceededTests() << " succeeded, " << results.NumberOfFailedTests() << " failed." << std::endl;
    }

  private:
    std::ostream& output_;
};

Context(VisualStudioResultsOutput_EmptyTestRun)
{
  std::auto_ptr<VisualStudioResultsOutput> output;
  std::stringstream resulting_stream;
  TestResults results;
  
  void SetUp()
  {
    output = std::auto_ptr<VisualStudioResultsOutput>(new VisualStudioResultsOutput(resulting_stream));
  }

  Spec(it_should_display_a_summary_line_with_no_tests_run)
  {
    output->PrintResult(results);

    Assert::That(resulting_stream.str(), Is().StartingWith("Test run complete. 0 tests run, 0 succeeded, 0 failed."));
  }
};
