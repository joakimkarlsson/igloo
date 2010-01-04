#ifndef IGLOO_ASSERTIONEXCEPTION_HPP
#define IGLOO_ASSERTIONEXCEPTION_HPP

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

#endif // IGLOO_ASSERTIONEXCEPTION_HPP
