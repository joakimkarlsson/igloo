#ifndef ASSERTIONEXCEPTION_HPP_WLWP5A27
#define ASSERTIONEXCEPTION_HPP_WLWP5A27

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

#endif /* end of include guard: ASSERTIONEXCEPTION_HPP_WLWP5A27 */

