#ifndef ASSERTIONEXCEPTION_HPP_WLWP5A27
#define ASSERTIONEXCEPTION_HPP_WLWP5A27

class AssertionException : public std::exception
{
public:  
	AssertionException(string message) : _message(message) {}
  virtual ~AssertionException() throw() {}
  
	string GetMessage() { return _message; }
	
private:
	string _message;	
};

#endif /* end of include guard: ASSERTIONEXCEPTION_HPP_WLWP5A27 */

