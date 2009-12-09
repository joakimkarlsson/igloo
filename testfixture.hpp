#ifndef TESTFIXTURE_HPP_K1ONTAQ7
#define TESTFIXTURE_HPP_K1ONTAQ7

#include "assertionexception.hpp"
#include "constraints/assertions.h"
#include "testresult.h"

class TestFixtureBase
{
public:
  virtual void Run(list<TestResult>& results) = 0;
};

#ifndef MAX_NUMBER_OF_TEST_METHODS   
#define MAX_NUMBER_OF_TEST_METHODS 100
#endif

template <typename T>
class TestFixture : public TestFixtureBase
{
public:
  typedef void (T::*TestMethodPtr)();
  typedef map<string, TestMethodPtr> TestMethods;

  void Run(list<TestResult>& results)
  {
    T testFixture;

    TestMethods testMethods;
    testFixture.GetTests(testMethods);
    CallTests(testFixture, testMethods, results);
  }

  void CallTests(T& t, TestMethods& testMethods, list<TestResult>& results)
  {
    typename TestMethods::iterator it;
    for (it = testMethods.begin(); it != testMethods.end(); it++)
    {
      cout << "Running test " << (*it).first << endl;
      CallTest(t, (*it).second, results);
    }
  }

  void CallTest(T t, void (T::*method)(), list<TestResult>& results)
  {
      try
      {
        (t.*method)();
      }
      catch (AssertionException& e)
      {
        results.push_back(TestResult("FIXTURE", "METHOD", false));
        cout << "Assertion failed in method " << e.GetMessage() << endl;
        return;
      }

        results.push_back(TestResult("FIXTURE", "METHOD", true));
  }

  void GetTests(TestMethods& testMethods)
  {
    #define REPEAT_SIGNATURE(z,n,name) name ## n (testMethods);
    BOOST_PP_REPEAT(MAX_NUMBER_OF_TEST_METHODS, REPEAT_SIGNATURE, GetTest)
      #undef REPEAT_SIGNATURE
  }

  #define REPEAT_SIGNATURE(z,n,name) virtual void name ## n (TestMethods&) {}
  BOOST_PP_REPEAT(MAX_NUMBER_OF_TEST_METHODS, REPEAT_SIGNATURE, GetTest)
  #undef REPEAT_SIGNATURE
};

#endif /* end of include guard: TESTFIXTURE_HPP_K1ONTAQ7 */
