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

  TestResult(string fixtureName, string methodName, bool success) :
  _fixtureName(fixtureName), _methodName(methodName), _success(success)
  {
  }

  string GetFixtureName() const
  {
    return _fixtureName;
  }

  string GetMethodName() const
  {
    return _methodName;
  }

  bool GetSuccess() const
  {
    return _success;
  }

private:
  string _fixtureName;
  string _methodName;
  bool _success;
};

#endif	/* _TESTRESULT_H */

