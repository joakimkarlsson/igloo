#ifndef ASSERTIONEXCEPTION_HPP_WLWP5A27
#define ASSERTIONEXCEPTION_HPP_WLWP5A27

class AssertionException : public std::exception
{
public:  
   AssertionException(const std::string message) : _message(message) {}
	virtual ~AssertionException() throw() {}
  
   std::string GetMessage() const { return _message; }
	
private:
   std::string _message;	
};

#endif /* end of include guard: ASSERTIONEXCEPTION_HPP_WLWP5A27 */

