/* 
* File:   testresult.h
* Author: joakim
*
* Created on December 8, 2009, 8:32 PM
*/

#ifndef IGLOO_TESTRESULT_H
#define	IGLOO_TESTRESULT_H

namespace igloo {
  class TestResult
  {
  public:
    TestResult(const std::string& fixtureName, const std::string& methodName, bool success)
      : _fixtureName(fixtureName), _methodName(methodName), _success(success)
    {
    }

    std::string GetFixtureName() const
    {
      return _fixtureName;
    }

    std::string GetMethodName() const
    {
      return _methodName;
    }

    bool GetSuccess() const
    {
      return _success;
    }

  private:
    std::string _fixtureName;
    std::string _methodName;
    bool _success;
  };
}

#endif /* IGLOO_TESTRESULT_H */

