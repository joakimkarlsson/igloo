#ifndef TESTFIXTURE_HPP_K1ONTAQ7
#define TESTFIXTURE_HPP_K1ONTAQ7

#include "assertionexception.hpp"
#include "assert.h"
#include "testresult.h"
#include "syntax.h"

namespace igloo {

  class TestFixtureBase
  {
  public:
    virtual void Run(const std::string& fixtureName, std::list<TestResult>& results) = 0;
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

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

  protected:

    RootNode Is()
    {
      return RootNode();
    }

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
        std::cout << "Test " << fixtureName << "::" << testName << " failed: " << std::endl << e.GetMessage() << std::endl;
        return;
      }


      results.push_back(TestResult(fixtureName, testName, true));
    }

    void GetTests(TestMethods& testMethods)
    {
      if(GetTest0(testMethods) == false) return;
      if(GetTest1(testMethods) == false) return;
      if(GetTest2(testMethods) == false) return;
      if(GetTest3(testMethods) == false) return;
      if(GetTest4(testMethods) == false) return;
      if(GetTest5(testMethods) == false) return;
      if(GetTest6(testMethods) == false) return;
      if(GetTest7(testMethods) == false) return;
      if(GetTest8(testMethods) == false) return;
      if(GetTest9(testMethods) == false) return;
      if(GetTest10(testMethods) == false) return;
      if(GetTest11(testMethods) == false) return;
      if(GetTest12(testMethods) == false) return;
      if(GetTest13(testMethods) == false) return;
      if(GetTest14(testMethods) == false) return;
      if(GetTest15(testMethods) == false) return;
      if(GetTest16(testMethods) == false) return;
      if(GetTest17(testMethods) == false) return;
      if(GetTest18(testMethods) == false) return;
      if(GetTest19(testMethods) == false) return;
      if(GetTest20(testMethods) == false) return;
      if(GetTest21(testMethods) == false) return;
      if(GetTest22(testMethods) == false) return;
      if(GetTest23(testMethods) == false) return;
      if(GetTest24(testMethods) == false) return;
      if(GetTest25(testMethods) == false) return;
      if(GetTest26(testMethods) == false) return;
      if(GetTest27(testMethods) == false) return;
      if(GetTest28(testMethods) == false) return;
      if(GetTest29(testMethods) == false) return;
      if(GetTest30(testMethods) == false) return;
      if(GetTest31(testMethods) == false) return;
      if(GetTest32(testMethods) == false) return;
      if(GetTest33(testMethods) == false) return;
      if(GetTest34(testMethods) == false) return;
      if(GetTest35(testMethods) == false) return;
      if(GetTest36(testMethods) == false) return;
      if(GetTest37(testMethods) == false) return;
      if(GetTest38(testMethods) == false) return;
      if(GetTest39(testMethods) == false) return;
      if(GetTest40(testMethods) == false) return;
      if(GetTest41(testMethods) == false) return;
      if(GetTest42(testMethods) == false) return;
      if(GetTest43(testMethods) == false) return;
      if(GetTest44(testMethods) == false) return;
      if(GetTest45(testMethods) == false) return;
      if(GetTest46(testMethods) == false) return;
      if(GetTest47(testMethods) == false) return;
      if(GetTest48(testMethods) == false) return;
      if(GetTest49(testMethods) == false) return;
      if(GetTest50(testMethods) == false) return;
      if(GetTest51(testMethods) == false) return;
      if(GetTest52(testMethods) == false) return;
      if(GetTest53(testMethods) == false) return;
      if(GetTest54(testMethods) == false) return;
      if(GetTest55(testMethods) == false) return;
      if(GetTest56(testMethods) == false) return;
      if(GetTest57(testMethods) == false) return;
      if(GetTest58(testMethods) == false) return;
      if(GetTest59(testMethods) == false) return;
      if(GetTest60(testMethods) == false) return;
      if(GetTest61(testMethods) == false) return;
      if(GetTest62(testMethods) == false) return;
      if(GetTest63(testMethods) == false) return;
      if(GetTest64(testMethods) == false) return;
      if(GetTest65(testMethods) == false) return;
      if(GetTest66(testMethods) == false) return;
      if(GetTest67(testMethods) == false) return;
      if(GetTest68(testMethods) == false) return;
      if(GetTest69(testMethods) == false) return;
      if(GetTest70(testMethods) == false) return;
      if(GetTest71(testMethods) == false) return;
      if(GetTest72(testMethods) == false) return;
      if(GetTest73(testMethods) == false) return;
      if(GetTest74(testMethods) == false) return;
      if(GetTest75(testMethods) == false) return;
      if(GetTest76(testMethods) == false) return;
      if(GetTest77(testMethods) == false) return;
      if(GetTest78(testMethods) == false) return;
      if(GetTest79(testMethods) == false) return;
      if(GetTest80(testMethods) == false) return;
      if(GetTest81(testMethods) == false) return;
      if(GetTest82(testMethods) == false) return;
      if(GetTest83(testMethods) == false) return;
      if(GetTest84(testMethods) == false) return;
      if(GetTest85(testMethods) == false) return;
      if(GetTest86(testMethods) == false) return;
      if(GetTest87(testMethods) == false) return;
      if(GetTest88(testMethods) == false) return;
      if(GetTest89(testMethods) == false) return;
      if(GetTest90(testMethods) == false) return;
      if(GetTest91(testMethods) == false) return;
      if(GetTest92(testMethods) == false) return;
      if(GetTest93(testMethods) == false) return;
      if(GetTest94(testMethods) == false) return;
      if(GetTest95(testMethods) == false) return;
      if(GetTest96(testMethods) == false) return;
      if(GetTest97(testMethods) == false) return;
      if(GetTest98(testMethods) == false) return;
      if(GetTest99(testMethods) == false) return;

      throw MaxNumberOfTestMethodsExceededException(100);
    }

  protected:
    virtual bool GetTest0(TestMethods&) { return false; }
    virtual bool GetTest1(TestMethods& ) { return false; }
    virtual bool GetTest2(TestMethods& ) { return false; }
    virtual bool GetTest3(TestMethods& ) { return false; }
    virtual bool GetTest4(TestMethods& ) { return false; }
    virtual bool GetTest5(TestMethods& ) { return false; }
    virtual bool GetTest6(TestMethods& ) { return false; }
    virtual bool GetTest7(TestMethods& ) { return false; }
    virtual bool GetTest8(TestMethods& ) { return false; }
    virtual bool GetTest9(TestMethods& ) { return false; }
    virtual bool GetTest10(TestMethods& ) { return false; }
    virtual bool GetTest11(TestMethods& ) { return false; }
    virtual bool GetTest12(TestMethods& ) { return false; }
    virtual bool GetTest13(TestMethods& ) { return false; }
    virtual bool GetTest14(TestMethods& ) { return false; }
    virtual bool GetTest15(TestMethods& ) { return false; }
    virtual bool GetTest16(TestMethods& ) { return false; }
    virtual bool GetTest17(TestMethods& ) { return false; }
    virtual bool GetTest18(TestMethods& ) { return false; }
    virtual bool GetTest19(TestMethods& ) { return false; }
    virtual bool GetTest20(TestMethods& ) { return false; }
    virtual bool GetTest21(TestMethods& ) { return false; }
    virtual bool GetTest22(TestMethods& ) { return false; }
    virtual bool GetTest23(TestMethods& ) { return false; }
    virtual bool GetTest24(TestMethods& ) { return false; }
    virtual bool GetTest25(TestMethods& ) { return false; }
    virtual bool GetTest26(TestMethods& ) { return false; }
    virtual bool GetTest27(TestMethods& ) { return false; }
    virtual bool GetTest28(TestMethods& ) { return false; }
    virtual bool GetTest29(TestMethods& ) { return false; }
    virtual bool GetTest30(TestMethods& ) { return false; }
    virtual bool GetTest31(TestMethods& ) { return false; }
    virtual bool GetTest32(TestMethods& ) { return false; }
    virtual bool GetTest33(TestMethods& ) { return false; }
    virtual bool GetTest34(TestMethods& ) { return false; }
    virtual bool GetTest35(TestMethods& ) { return false; }
    virtual bool GetTest36(TestMethods& ) { return false; }
    virtual bool GetTest37(TestMethods& ) { return false; }
    virtual bool GetTest38(TestMethods& ) { return false; }
    virtual bool GetTest39(TestMethods& ) { return false; }
    virtual bool GetTest40(TestMethods& ) { return false; }
    virtual bool GetTest41(TestMethods& ) { return false; }
    virtual bool GetTest42(TestMethods& ) { return false; }
    virtual bool GetTest43(TestMethods& ) { return false; }
    virtual bool GetTest44(TestMethods& ) { return false; }
    virtual bool GetTest45(TestMethods& ) { return false; }
    virtual bool GetTest46(TestMethods& ) { return false; }
    virtual bool GetTest47(TestMethods& ) { return false; }
    virtual bool GetTest48(TestMethods& ) { return false; }
    virtual bool GetTest49(TestMethods& ) { return false; }
    virtual bool GetTest50(TestMethods& ) { return false; }
    virtual bool GetTest51(TestMethods& ) { return false; }
    virtual bool GetTest52(TestMethods& ) { return false; }
    virtual bool GetTest53(TestMethods& ) { return false; }
    virtual bool GetTest54(TestMethods& ) { return false; }
    virtual bool GetTest55(TestMethods& ) { return false; }
    virtual bool GetTest56(TestMethods& ) { return false; }
    virtual bool GetTest57(TestMethods& ) { return false; }
    virtual bool GetTest58(TestMethods& ) { return false; }
    virtual bool GetTest59(TestMethods& ) { return false; }
    virtual bool GetTest60(TestMethods& ) { return false; }
    virtual bool GetTest61(TestMethods& ) { return false; }
    virtual bool GetTest62(TestMethods& ) { return false; }
    virtual bool GetTest63(TestMethods& ) { return false; }
    virtual bool GetTest64(TestMethods& ) { return false; }
    virtual bool GetTest65(TestMethods& ) { return false; }
    virtual bool GetTest66(TestMethods& ) { return false; }
    virtual bool GetTest67(TestMethods& ) { return false; }
    virtual bool GetTest68(TestMethods& ) { return false; }
    virtual bool GetTest69(TestMethods& ) { return false; }
    virtual bool GetTest70(TestMethods& ) { return false; }
    virtual bool GetTest71(TestMethods& ) { return false; }
    virtual bool GetTest72(TestMethods& ) { return false; }
    virtual bool GetTest73(TestMethods& ) { return false; }
    virtual bool GetTest74(TestMethods& ) { return false; }
    virtual bool GetTest75(TestMethods& ) { return false; }
    virtual bool GetTest76(TestMethods& ) { return false; }
    virtual bool GetTest77(TestMethods& ) { return false; }
    virtual bool GetTest78(TestMethods& ) { return false; }
    virtual bool GetTest79(TestMethods& ) { return false; }
    virtual bool GetTest80(TestMethods& ) { return false; }
    virtual bool GetTest81(TestMethods& ) { return false; }
    virtual bool GetTest82(TestMethods& ) { return false; }
    virtual bool GetTest83(TestMethods& ) { return false; }
    virtual bool GetTest84(TestMethods& ) { return false; }
    virtual bool GetTest85(TestMethods& ) { return false; }
    virtual bool GetTest86(TestMethods& ) { return false; }
    virtual bool GetTest87(TestMethods& ) { return false; }
    virtual bool GetTest88(TestMethods& ) { return false; }
    virtual bool GetTest89(TestMethods& ) { return false; }
    virtual bool GetTest90(TestMethods& ) { return false; }
    virtual bool GetTest91(TestMethods& ) { return false; }
    virtual bool GetTest92(TestMethods& ) { return false; }
    virtual bool GetTest93(TestMethods& ) { return false; }
    virtual bool GetTest94(TestMethods& ) { return false; }
    virtual bool GetTest95(TestMethods& ) { return false; }
    virtual bool GetTest96(TestMethods& ) { return false; }
    virtual bool GetTest97(TestMethods& ) { return false; }
    virtual bool GetTest98(TestMethods& ) { return false; }
    virtual bool GetTest99(TestMethods& ) { return false; }

  };
}
#endif /* end of include guard: TESTFIXTURE_HPP_K1ONTAQ7 */
