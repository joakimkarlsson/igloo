
#include "assertionexception.hpp"

#ifndef TESTRUNNER_HPP_X6IAF59Y
#define TESTRUNNER_HPP_X6IAF59Y

class TestRunner
{
public:
  typedef map<string, TestFixtureBase* > TestFixtureMap;
  static TestFixtureMap FixtureMap;

  static void RunAllTests()
  {
    for (TestFixtureMap::iterator it = FixtureMap.begin(); it != FixtureMap.end(); it++)
    {
      cout << "Running test fixture: " << (*it).first << endl;
      (*it).second->Run();
    }
  }
};
TestRunner::TestFixtureMap TestRunner::FixtureMap;

#endif /* end of include guard: TESTRUNNER_HPP_X6IAF59Y */
