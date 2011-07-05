
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTRUNNER_H
#define IGLOO_TESTRUNNER_H

#include <igloo/core/testresult.h>
#include <igloo/core/testresults.h>

namespace igloo {
  class TestRunner
  {
  public:
    typedef std::pair<std::string, BaseContextRunner*> NamedContextRunner;
    typedef std::vector<NamedContextRunner> ContextRunners;
    
    static int RunAllTests()
    {
      TestResults results;
      
      for (ContextRunners::iterator it = RegisteredRunners().begin(); it != RegisteredRunners().end(); it++)
      {
        std::auto_ptr<BaseContextRunner> contextRunner((*it).second);
        contextRunner->Run((*it).first, results);
      }
      
      RegisteredRunners().clear();
      
      std::cout << std::endl;
      
      return CheckResults(results);
    }
    
    static int CheckResults(const TestResults& results)
    {
      for (TestResults::const_iterator it = results.begin(); it != results.end(); it++)
      {
        const TestResult& result = *it;
        if (!result.GetSuccess())
        {
          std::cout << result.GetContextName() << "::" << result.GetSpecName() << " failed:" << std::endl << result.GetErrorMessage() << std::endl;
        }
      }
      
      std::cout << "Test run complete. " << results.NumberOfTestsRun() << " tests run, " << results.NumberOfSucceededTests() << " succeeded, " << results.NumberOfFailedTests() << " failed." << std::endl;
      return results.NumberOfFailedTests();
    }
    
    template <typename ContextRunnerType>
    static void RegisterContext(const std::string& name)
    {
      if(!ContextIsRegistered(name))
      {
        ContextRunnerType* contextRunner = 0;

        try
        {
          // Must add runner first...
          contextRunner = new ContextRunnerType;
          TestRunner::RegisteredRunners().push_back(std::make_pair(name, contextRunner));

          // ... and then instantiate context, because context ctor calls this method again,
          // possibly for the same context, depending on inheritance chain.
          contextRunner->InstantiateContext();
        }
        catch (...)
        {
          delete contextRunner;
          throw;
        }
      }
    }
    
    static bool ContextIsRegistered(const std::string& name)
    {
      for (ContextRunners::const_iterator it = RegisteredRunners().begin(); it != RegisteredRunners().end(); ++it)
      {
        if((*it).first == name)
        {
          return true;
        }
      }
      
      return false;
    }
    
    static TestRunner::ContextRunners& RegisteredRunners()
    {
      static TestRunner::ContextRunners contextRunners;
      return contextRunners;
    }
  };
}

#endif // IGLOO_TESTRUNNER_H
