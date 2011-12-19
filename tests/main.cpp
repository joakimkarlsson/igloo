
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

using namespace igloo;

class ProgressWritingTestListener : public TestListener
{
  public:
  void TestRunStarting()
  {
    std::cout << "Test run is starting..." << std::endl;
  }

  void TestRunEnded(const TestResults& )
  {
    std::cout << "Test run ended." << std::endl;
  }

  void ContextRunStarting(const std::string& contextName, const MetaData& metadata)
  {
    std::cout << "Starting test for context " << contextName << " with category " << metadata.GetMetaData("category") << std::endl;
  }
  
  void ContextRunEnded(const std::string& contextName, const MetaData& metadata)
  {
    std::cout << "Ending test for context " << contextName << " with category " << metadata.GetMetaData("category") << std::endl;
  }
};

//int main()
//{
//  DefaultTestResultsOutput output;
//  TestRunner runner(output);
//
//  ProgressWritingTestListener listener;
//
//  runner.AddListener(&listener);
//
//  runner.Run();
//}

int main()
{
  return TestRunner::RunAllTests();
}
