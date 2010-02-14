#include <tests/igloo_self_test.h>

using namespace igloo;

struct Common : public BaseFixture<Common>
{
  virtual ~Common() {}
  virtual void SpecificSetUp() = 0;
  
  void SetUp()
  {
    SpecificSetUp();
  }
  
  TestMethod(TestIt)
  {
    Assert::That(val, Is().LessThan(4));
  }
  
  int val;
};

DerivedFixture(Specific1, Common)
{
  virtual ~Specific1() {}
  void SpecificSetUp()
  {
    val = 3;
  }
};

DerivedFixture(Specific2, Common)
{
  virtual ~Specific2() {}
  void SpecificSetUp()
  {
    val = 2;
  }
};
