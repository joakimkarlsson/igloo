#ifndef IGLOO_XUNITOUTPUT_H
#define IGLOO_XUNITOUTPUT_H

#include <typeinfo>

#include <igloo/core/outputters/xmlwritter.h>

namespace igloo {
  class XUnitTestsOutput : public TestResultsOutput
  {
    public:

      void PrintResult(const TestResults& results) const
			{
				xml::writer xw(output); {
					xml::element tag("testsuite", xw); 
					{
						tag.attr("name", "Igloo");
						tag.attr("tests", results.NumberOfTestsRun());
						tag.attr("errors", 0);
						tag.attr("failures", results.NumberOfFailedTests());

						for (TestResults::TestsType::const_iterator it = results.Tests().begin();
																												it != results.Tests().end();
																												it++)
						{
							const TestResult& result = *it;

							xml::element tag("testcase", xw); {
								tag.attr("classname", result.GetContextName());
								tag.attr("name", result.GetSpecName());
								tag.attr("time", 0);
								try 
								{
									const FailedTestResult& failed = dynamic_cast<const FailedTestResult&>(result);
									xml::element tag("failure", xw); {
										tag.attr("message", failed.GetErrorMessage());
									}
								}
								catch(std::bad_cast exp)
								{
								}
							}
						}
					}
				}
      }
  };
}



#endif

