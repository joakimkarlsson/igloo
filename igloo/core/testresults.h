
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTRESULTS_H
#define IGLOO_TESTRESULTS_H

namespace igloo {

  class TestResults 
  {
    public:

      int NumberOfTestsRun() const
      {
        return NumberOfSucceededTests() + NumberOfFailedTests();
      }

      int NumberOfSucceededTests() const
      {
        return succeededTests_.size();
      }

      int NumberOfFailedTests() const
      {
        return failedTests_.size();
      }

      void AddResult(const TestResult result)
      {
        if(result.GetSuccess())
        {
          succeededTests_.push_back(result);
        }
        else
        {
          failedTests_.push_back(result);
        }
      }

      typedef std::list<TestResult>::const_iterator const_iterator;

      const std::list<TestResult>& FailedTests() const
      {
        return failedTests_;
      }

      const std::list<TestResult>& SucceededTests() const
      {
        return succeededTests_;
      }

      friend std::ostream& operator<<(std::ostream& stm, const TestResults& results);

    private:
      std::list<TestResult> failedTests_;
      std::list<TestResult> succeededTests_;

      static bool SpecSucceeded(const TestResult& spec)
      {
        return spec.GetSuccess();
      }
  };


  inline std::ostream& operator<<(std::ostream& stm, const TestResults& results)
  {
    stm << "[ ";
    TestResults::const_iterator it;
    for(it = results.FailedTests().begin(); it != results.FailedTests().end(); it++)
    {
      stm << "< " << *it << " >";
    }

    for(it = results.SucceededTests().begin(); it != results.SucceededTests().end(); it++)
    {
      stm << "< " << *it << " >";
    }

    stm << " ]";

    return stm;
  }
}

#endif
