#ifndef TESTFIXTURE_HPP_K1ONTAQ7
#define TESTFIXTURE_HPP_K1ONTAQ7

#include "assertionexception.hpp"
#include "assert.h"
#include "testresult.h"

namespace igloo {
   class TestFixtureBase
   {
   public:
      virtual void Run(const std::string& fixtureName, std::list<TestResult>& results) = 0;
   };

#ifndef MAX_NUMBER_OF_TEST_METHODS   
#define MAX_NUMBER_OF_TEST_METHODS 100
#endif

   template <typename T>
   class TestFixture : public TestFixtureBase
   {
   public:
      typedef void (T::*TestMethodPtr)();
      typedef std::map<std::string, TestMethodPtr> TestMethods;

      void Run(const std::string& fixtureName, std::list<TestResult>& results)
      {
         T testFixture;

         TestMethods testMethods;
         testFixture.GetTests(testMethods);
         CallTests(testFixture, testMethods, fixtureName, results);
      }

      virtual void SetUp() {}
      virtual void TearDown() {}

   private:
      void CallTests(T& t, TestMethods& testMethods, std::string fixtureName, std::list<TestResult>& results)
      {
         typename TestMethods::iterator it;
         for (it = testMethods.begin(); it != testMethods.end(); it++)
         {
            std::cout << "Running test " << (*it).first << std::endl;
            CallTest(t, fixtureName, (*it).first, (*it).second, results);
         }
      }

      void CallTest(T t, const std::string& fixtureName, const std::string& testName, void (T::*method)(), std::list<TestResult>& results)
      {
         try
         {
            t.SetUp();
            (t.*method)();
            t.TearDown();
         }
         catch (AssertionException& e)
         {
            results.push_back(TestResult(fixtureName, testName, false));
            std::cout << "Test " << fixtureName << "::" << testName << " failed: " << e.GetMessage() << std::endl;
            return;
         }


         results.push_back(TestResult(fixtureName, testName, true));
      }

      void GetTests(TestMethods& testMethods)
      {
         #define REPEAT_SIGNATURE(z,n,name) if(name ## n (testMethods) == false) return;
         BOOST_PP_REPEAT(MAX_NUMBER_OF_TEST_METHODS, REPEAT_SIGNATURE, GetTest)
         #undef REPEAT_SIGNATURE
      }

   protected:
      #define REPEAT_SIGNATURE(z,n,name) virtual bool name ## n (TestMethods&) { return false;}
      BOOST_PP_REPEAT(MAX_NUMBER_OF_TEST_METHODS, REPEAT_SIGNATURE, GetTest)
      #undef REPEAT_SIGNATURE
   };
}
#endif /* end of include guard: TESTFIXTURE_HPP_K1ONTAQ7 */
