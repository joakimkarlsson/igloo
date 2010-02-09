#ifndef IGLOO_TESTFIXTURERUNNER_H
#define IGLOO_TESTFIXTURERUNNER_H

#include <list>

namespace igloo {

   struct TestFixtureRunnerBase
   {
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
         typename FixtureRunnerInfo<BaseFixtureType, FixtureType>::FixtureToInstantiate testFixture;
         BaseFixture<typename FixtureRunnerInfo<BaseFixtureType, FixtureType>::FixtureToCall>::Run(testFixture, fixtureName, results);
      }
   };
}

#endif
