#ifndef IGLOO_TESTRUNNER_H
#define IGLOO_TESTRUNNER_H

#include <list>
#include "igloo/core/testresult.h"

namespace igloo {
  class TestRunner
  {
  public:
    typedef std::map<std::string, TestFixtureRunnerBase* > TestFixtureRunners;
    
    static int RunAllTests()
    {
      std::list<TestResult> results;
      
      for (TestFixtureRunners::iterator it = FixtureRunners().begin(); it != FixtureRunners().end(); it++)
      {
        (*it).second->Run((*it).first, results);
        delete (*it).second;
      }
      
      FixtureRunners().clear();
      
      std::cout << std::endl;
      
      return CheckResults(results);
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
          
          const TestResult& result = *it;
          
          std::cout << result.GetFixtureName() << "::" << result.GetMethodName() << " failed:" << std::endl << result.GetErrorMessage() << std::endl;
        }
      }
      
      std::cout << "Test run complete. " << run << " tests run, " << succeeded << " succeeded, " << failed << " failed." << std::endl;
      return failed;
    }
    
    template <typename FixtureRunnerType>
    static void RegisterTestFixture(const std::string& name)
    {
      TestRunner::FixtureRunners()[name] = new FixtureRunnerType();
    }
    
    static TestRunner::TestFixtureRunners& FixtureRunners()
    {
      static TestRunner::TestFixtureRunners _fixtureRunners;
      return _fixtureRunners;
    }
  };
}

#endif // IGLOO_TESTRUNNER_H
