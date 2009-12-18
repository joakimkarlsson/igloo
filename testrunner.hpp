#ifndef TESTRUNNER_HPP_X6IAF59Y
#define TESTRUNNER_HPP_X6IAF59Y

#include <list>
#include "assertionexception.hpp"
#include "testresult.h"

namespace igloo {
   class TestRunner
   {
   public:
      typedef std::map<std::string, TestFixtureBase* > TestFixtureMap;
      static TestFixtureMap FixtureMap;

      static int RunAllTests()
      {
         std::list<TestResult> results;

         for (TestFixtureMap::iterator it = FixtureMap.begin(); it != FixtureMap.end(); it++)
         {
            std::cout << "Running test fixture: " << (*it).first << std::endl;
            (*it).second->Run((*it).first, results);
         }

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
            }
         }

         std::cout << "Test run complete. " << run << " tests run, " << succeeded << " succeeded, " << failed << " failed." << std::endl;
         return failed;
      }
   };
   TestRunner::TestFixtureMap TestRunner::FixtureMap;
}
#endif /* end of include guard: TESTRUNNER_HPP_X6IAF59Y */
