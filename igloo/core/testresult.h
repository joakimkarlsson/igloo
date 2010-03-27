//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_TESTRESULT_H
#define IGLOO_TESTRESULT_H

namespace igloo {

  class TestResult
  {
  public:
    TestResult(const std::string& contextName, const std::string& specName, bool success, const std::string& errorMessage)
      : m_contextName(contextName), m_specName(specName), m_success(success), m_errorMessage(errorMessage)
    {
    }

    const std::string& GetContextName() const
    {
      return m_contextName;
    }

    const std::string& GetSpecName() const
    {
      return m_specName;
    }

    bool GetSuccess() const
    {
      return m_success;
    }

    const std::string& GetErrorMessage() const
    {
      return m_errorMessage;
    }
    
    bool operator==(const TestResult& rhs) const
    {
      return m_contextName == rhs.m_contextName &&
      m_specName == rhs.m_specName &&
      m_success == rhs.m_success &&
      m_errorMessage == rhs.m_errorMessage;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const TestResult& res);

  private:
    std::string m_contextName;
    std::string m_specName;
    bool m_success;
    std::string m_errorMessage;
  };

  inline std::ostream& operator<<(std::ostream& stream, const TestResult& res)
  {
    stream
      << "TestResult ( m_contextName=" << res.m_contextName
      << ", m_specName=" << res.m_specName
      << ", m_success=" << res.m_success
      << ", m_errorMessage=" << res.m_errorMessage
      << " )";

    return stream;
  }

}

#endif /* IGLOO_TESTRESULT_H */

