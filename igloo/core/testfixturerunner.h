
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTFIXTURERUNNER_H
#define IGLOO_TESTFIXTURERUNNER_H

#include <list>

namespace igloo {
  
  struct TestFixtureRunnerBase
  {
    virtual ~TestFixtureRunnerBase() {}
    virtual void Run(const std::string& fixtureName, std::list<TestResult>& results) = 0;    
  };
  
  template <typename BaseFixtureType, typename FixtureType>
  struct FixtureRunnerInfo
  {
    typedef BaseFixtureType FixtureToCall;
    typedef FixtureType FixtureToInstantiate;
  };
  
  template <typename FixtureType>
  struct FixtureRunnerInfo<void, FixtureType>
  {
    typedef FixtureType FixtureToCall;
    typedef FixtureType FixtureToInstantiate;
  };

  template <typename BaseFixtureType, typename FixtureType>
  class TestFixtureRunner : public TestFixtureRunnerBase
  {
  public:   
    void Run(const std::string& fixtureName, std::list<TestResult>& results)
    {
      typedef typename FixtureRunnerInfo<BaseFixtureType, FixtureType>::FixtureToCall FTC;
      typedef typename FixtureRunnerInfo<BaseFixtureType, FixtureType>::FixtureToInstantiate FTI;
      typedef BaseFixture<FTC> BF;

      BF::template Run<FTI>(fixtureName, results);
    }
  };
}

#endif
