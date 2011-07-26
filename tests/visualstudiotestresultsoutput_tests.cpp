
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
      TestResults::FailedTestsType::const_iterator it;

      for(it = results.FailedTests().begin(); it != results.FailedTests().end(); it++)
      {
        output_ << FormatOriginString(*it) << " : assertion failed error I001: " << (*it).GetContextName() << "::" << (*it).GetSpecName() << ": " << (*it).GetErrorMessage() << std::endl;
      }

      output_ << "Test run complete. " << results.NumberOfTestsRun() << " tests run, " << results.NumberOfSucceededTests() << " succeeded, " << results.NumberOfFailedTests() << " failed." << std::endl;
    }

  private:

    std::string FormatOriginString(const FailedTestResult& result)
    {
      if(result.HasLineNumber() && result.HasFilename())
      {
        std::ostringstream builder;
        builder << result.Filename() << "(" << result.LineNumber() << ")";
        return builder.str();
      }
      
      // Default to toolname if no location information is available
      return "Igloo";
    }

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
    output->PrintResult(results);
  }

  Spec(it_should_display_a_summary_line_with_no_tests_run)
  {
    Assert::That(resulting_stream.str(), Is().StartingWith("Test run complete. 0 tests run, 0 succeeded, 0 failed."));
  }

  Context(VisualStudioResultsOutput_one_failed_test_with_no_location_information)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A failing spec", "The error message"));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(it_displays_one_failing_test_in_summary)
    {
      AssertThat(resulting_output(), Has().Exactly(1).StartingWith("Test run complete. 1 tests run, 0 succeeded, 1 failed"));
    }

    Spec(it_displays_error_text_for_failed_spec_with_no_location_information)
    {
      AssertThat(resulting_output(), Is().Containing("Igloo : assertion failed error I001: A context name::A failing spec: The error message"));
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

  Context(VisualStudioResultOutput_one_failed_test_with_information_about_location_of_assertion)
  {
    void SetUp()
    {
      testResults().AddResult(FailedTestResult("A context name", "A failing spec", "The error message", "filename.cpp", 23));
      Parent().output->PrintResult(Parent().results);
    }

    Spec(it_displays_one_failing_test_in_summary)
    {
      AssertThat(resulting_output(), Has().Exactly(1).StartingWith("Test run complete. 1 tests run, 0 succeeded, 1 failed"));
    }

    Spec(it_displays_error_text_for_failed_spec_with_location_information)
    {
      AssertThat(resulting_output(), Has().Exactly(1).StartingWith("filename.cpp(23) : assertion failed error I001: A context name::A failing spec: The error message"));
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
