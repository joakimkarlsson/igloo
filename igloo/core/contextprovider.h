
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_CONTEXTPROVIDER_H_
#define IGLOO_CONTEXTPROVIDER_H_

namespace igloo {
  
  namespace detail {
    template <typename T>
      inline bool IsOnlyTemplate()
      {
        return T::IsOnly_Static();
      }

    template <>
      inline bool IsOnlyTemplate<ContextWithAttribute<void> >()
      {
        return false;
      }
  }

  template <typename InnerContext, typename OuterContext, bool ISONLY>
    struct ContextProvider : public igloo::ContextWithAttribute<InnerContext>
  {
    typedef InnerContext IGLOO_CURRENT_CONTEXT;
    typedef InnerContext IGLOO_OUTER_CONTEXT;

    static bool IsOnly_Static()
    {
      return ISONLY || detail::IsOnlyTemplate<OuterContext>();
    }

    virtual OuterContext& Parent()
    {
      if(m_outerContext.get() == 0)
      {
        m_outerContext = std::auto_ptr<OuterContext>(CreateIglooContext<OuterContext>());
      }
      return *(m_outerContext.get());
    }

    virtual void IglooFrameworkSetUp()
    {
      Parent().IglooFrameworkSetUp();
      this->SetUp();
    }

    virtual void IglooFrameworkTearDown()
    {
      this->TearDown();
      Parent().IglooFrameworkTearDown();
    }


    private:
    template <typename ContextType>
      ContextType* CreateIglooContext()
      {
        return new ContextType();
      }

    std::auto_ptr<OuterContext> m_outerContext;
  };
}
#endif
