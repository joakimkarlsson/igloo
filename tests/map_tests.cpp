#include "igloo_self_test.h"

using namespace igloo;

TestFixture(MapTests)
{
  std::map<std::string, int> ages;
  
  void SetUp()
  {
    ages["joakim"] = 38;
    ages["maria"] = 36;
    ages["hanna"] = 6;
    ages["moa"] = 4;
  }
  
  TestMethod(ContainingShouldDetermineIfKeyExists)
  {
    Assert::That(ages, Is().Containing("joakim"));
  }
};
