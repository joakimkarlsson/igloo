#include "igloo/tests/igloo_self_test.h"

using namespace igloo;

struct Common : public BaseFixture<Common>
{
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
   void SpecificSetUp()
   {
      val = 3;
   }
};

DerivedFixture(Specific2, Common)
{
   void SpecificSetUp()
   {
      val = 2;
   }
};
