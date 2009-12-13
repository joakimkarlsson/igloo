#ifndef TESTRUNNER_HPP_X6IAF59Y
#define TESTRUNNER_HPP_X6IAF59Y

#include <list>
#include "assertionexception.hpp"
#include "testresult.h"

class TestRunner
{
public:
  typedef map<string, TestFixtureBase* > TestFixtureMap;
  static TestFixtureMap FixtureMap;

  static int RunAllTests()
  {
    list<TestResult> results;

    for (TestFixtureMap::iterator it = FixtureMap.begin(); it != FixtureMap.end(); it++)
    {
      cout << "Running test fixture: " << (*it).first << endl;
      (*it).second->Run((*it).first, results);
    }

    return CheckResults(results);
  }

  static int CheckResults(const list<TestResult>& results)
  {
    int run = 0, succeeded = 0, failed = 0;

    for (list<TestResult>::const_iterator it = results.begin(); it != results.end(); it++)
    {
      run++;
      if ((*it).GetSuccess())
      {
        succeeded++;
      }
      else
      {
        failed++;
      }
    }

    cout << "Test run complete. " << run << " tests run, " << succeeded << " succeeded, " << failed << " failed." << endl;
    return failed;
  }
};
TestRunner::TestFixtureMap TestRunner::FixtureMap;

#endif /* end of include guard: TESTRUNNER_HPP_X6IAF59Y */
