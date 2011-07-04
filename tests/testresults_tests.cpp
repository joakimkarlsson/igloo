
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

class TestResults
{
  public:
    TestResults() : testCount_(0), testsFailedCount_(0)
    {
    }

    int NumberOfTestsRun() const
    {
      return testCount_;
    }

    int NumberOfSucceededTests() const
    {
      return 0;
    }

    int NumberOfFailedTests() const
    {
      return testsFailedCount_;
    }

    void AddResult(const TestResult& )
    {
      testCount_++;
      testsFailedCount_++;
    }

  private:
    int testCount_;
    int testsFailedCount_;
};

Context(An_empty_test_run)
{
  TestResults results;

  Spec(Number_of_tests_should_be_0)
  {
    Assert::That(results.NumberOfTestsRun(), Is().EqualTo(0));
  }

  Spec(Number_of_failed_tests_should_be_0)
  {
    Assert::That(results.NumberOfFailedTests(), Is().EqualTo(0));
  }

  Spec(Number_of_succeeded_tests_should_be_0)
  {
    Assert::That(results.NumberOfSucceededTests(), Is().EqualTo(0));
  }

  Context(One_failed_test)
  {
    void SetUp()
    {
      Results().AddResult(TestResult("The context name", "The test name", false, "The error message"));
    }

    Spec(Number_of_tests_should_be_1)
    {
      Assert::That(Results().NumberOfTestsRun(), Is().EqualTo(1));
    }

    Spec(Number_of_failed_tests_should_be_1)
    {
      Assert::That(Results().NumberOfFailedTests(), Is().EqualTo(1));
    }

    Spec(Number_of_succeeded_tests_should_be_0)
    {
      Assert::That(Results().NumberOfSucceededTests(), Is().EqualTo(0));
    }

    TestResults& Results()
    {
      return Parent().results;
    }
  };
};
