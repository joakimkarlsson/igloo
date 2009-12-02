#include <iostream>
#include <sstream>
#include <map>    
#include <vector>    
#include <boost/preprocessor.hpp>   
#include <memory>
#include "igloo.hpp"

TestFixture(AssertionTests)
{
  public:

  TestMethod(AssertionTests, TestEquality)
  {
    Assert::That(5, Is::EqualTo(4));
  }

  TestMethod(AssertionTests, Test2)
  {
    Assert::That("Joakim", Is::EqualTo("Harry"));
  }
};

int main()
{
  TestRunner::RunAllTests();
  return 0;
}