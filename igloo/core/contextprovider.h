
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_CONTEXTPROVIDER_H_
#define IGLOO_CONTEXTPROVIDER_H_

// Default current context to empty base class
typedef igloo::ContextBase IGLOO_CURRENT_CONTEXT;

template <typename InnerContext, typename OuterContext>
struct ContextProvider 
	: public OuterContext
{
  typedef InnerContext IGLOO_CURRENT_CONTEXT;
  
  virtual void IglooFrameworkSetUp()
  {
	OuterContext::IglooFrameworkSetUp();
	Call(&InnerContext::SetUp);
  }
  
  virtual void IglooFrameworkTearDown()
  {
	Call(&InnerContext::TearDown);
    OuterContext::IglooFrameworkTearDown();
  }

private:
	void Call(void (InnerContext::*Method)())
	{
		(static_cast<InnerContext*>(this)->*Method)();
	}
};

#endif
