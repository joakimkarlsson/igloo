#ifndef IGLOO_TESTFIXTURE_H
#define IGLOO_TESTFIXTURE_H

#include "assertionexception.h"
#include "assert.h"
#include "testresult.h"
#include "syntax.h"
               

	template <typename FixtureType, int MethodSlot, typename DUMMIEE = void>
	struct test_slot
	{
		static void reg(std::map<std::string, void (FixtureType::*)()>&)
		{
		}
	};
	
namespace igloo {

  class TestFixtureBase
  {
  public:
    virtual void Run(const std::string& fixtureName, std::list<TestResult>& results) = 0;

  protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    RootNode Is()
    {
      RootNode node;
      return node;
    }
  };

  class MaxNumberOfTestMethodsExceededException
  {
  public:
    MaxNumberOfTestMethodsExceededException(int max) : m_max(max) {}

    int GetMax() const
    {
      return m_max;
    }

  private:
    int m_max;
  };
                        

  template <typename T, int FirstMethodSlot>
  class TestFixture : public TestFixtureBase
  {
  public:
    typedef T IGLOO_FIXTURE_TYPE;

    void Run(const std::string& fixtureName, std::list<TestResult>& results)
    {
      T testFixture;

      TestMethods testMethods;
      testFixture.GetTests(testMethods);
      CallTests(testFixture, testMethods, fixtureName, results);
    }

  private:
    typedef void (T::*TestMethodPtr)();
    typedef std::map<std::string, TestMethodPtr> TestMethods;

    void CallTests(T& t, TestMethods& testMethods, const std::string& fixtureName, std::list<TestResult>& results)
    {
      typename TestMethods::iterator it;
      for (it = testMethods.begin(); it != testMethods.end(); it++)
      {
        if(CallTest(t, fixtureName, (*it).first, (*it).second, results))
        {
           std::cout << ".";
        }
        else
        {
           std::cout << "F";
        }
      }
    }

    bool CallTest(T t, const std::string& fixtureName, const std::string& testName, TestMethodPtr method, std::list<TestResult>& results)
    {
      try
      {
        t.SetUp();
        (t.*method)();
        t.TearDown();
      }
      catch (const AssertionException& e)
      {
        results.push_back(TestResult(fixtureName, testName, false, e.GetMessage()));
        return false;
      }

      results.push_back(TestResult(fixtureName, testName, true, "Test succeeded"));
      return true;
    }

    void GetTests(TestMethods& testMethods)
    {                                
			test_slot<T, FirstMethodSlot+1>::reg(testMethods);
    }
  };
}

#endif // IGLOO_TESTFIXTURE_H
