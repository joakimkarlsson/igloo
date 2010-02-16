
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_ASSERTIONEXCEPTION_H
#define IGLOO_ASSERTIONEXCEPTION_H

namespace igloo {
  class AssertionException : public std::exception
  {
  public:  
  AssertionException(const std::string& message)
    : m_message(message)
  {
  }

  virtual ~AssertionException() throw()
  {
  }

  std::string GetMessage() const
  {
    return m_message;
  }

  private:
  std::string m_message;  
  };
}

#endif // IGLOO_ASSERTIONEXCEPTION_H
