#ifndef IGLOO_TESTRUNNER_HPP
#define IGLOO_TESTRUNNER_HPP

#include <list>
#include "assertionexception.hpp"
#include "testresult.h"

namespace igloo {
  class TestRunner
  {
  public:
    typedef std::map<std::string, TestFixtureBase* > TestFixtureMap;

    static int RunAllTests()
    {
      try
      {
        std::list<TestResult> results;

        for (TestFixtureMap::iterator it = FixtureMap().begin(); it != FixtureMap().end(); it++)
        {
          std::cout << "Running test fixture: " << (*it).first << std::endl;
          (*it).second->Run((*it).first, results);
          std::cout << std::endl;
        }

        return CheckResults(results);
      }
      catch(const MaxNumberOfTestMethodsExceededException& exception)
      {
        std::cout << std::endl << "ERROR: The maximum number of test methods (" << exception.GetMax() << ") for one test fixture has been exceeded" << std::endl;
      }

      return 0;
    }

    static int CheckResults(const std::list<TestResult>& results)
    {
      int run = 0, succeeded = 0, failed = 0;

      for (std::list<TestResult>::const_iterator it = results.begin(); it != results.end(); it++)
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

      std::cout << "Test run complete. " << run << " tests run, " << succeeded << " succeeded, " << failed << " failed." << std::endl;
      return failed;
    }

    static int RegisterTestFixture(std::string name, TestFixtureBase* testFixture)
    {
      TestRunner::FixtureMap()[name] = testFixture;
      return 0;
    }

    static TestRunner::TestFixtureMap& FixtureMap()
    {
      static TestRunner::TestFixtureMap _fixtureMap;
      return _fixtureMap;
    }
  };
}

#endif // IGLOO_TESTRUNNER_HPP
