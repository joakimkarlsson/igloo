/* 
 * File:   testresult.h
 * Author: joakim
 *
 * Created on December 8, 2009, 8:32 PM
 */

#ifndef _TESTRESULT_H
#define	_TESTRESULT_H

class TestResult
{
public:

   TestResult(std::string fixtureName, std::string methodName, bool success) :
  _fixtureName(fixtureName), _methodName(methodName), _success(success)
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

#endif	/* _TESTRESULT_H */

