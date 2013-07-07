
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_CONTEXTPROVIDER_H_
#define IGLOO_CONTEXTPROVIDER_H_

namespace igloo {
  
  namespace detail {
    //
    // Check is the context is marked as "only"
    //
    template <typename T>
      inline bool IsMarkedAsOnly()
      {
        return T::IsMarkedAsOnly();
      }

    //
    // Specialization for root context. Is never marked "only".
    //
    template <>
    inline bool IsMarkedAsOnly<ContextWithAttribute<void> >()
    {
      return false;
    }

    template <typename T>
    inline bool IsContextMarkedAsSkip()
    {
      return T::IsMarkedAsSkip();
    }

    template <>
    inline bool IsContextMarkedAsSkip<ContextWithAttribute<void> >()
    {
      return false;
    }
  }

  template <typename InnerContext, typename OuterContext, bool ISONLY, bool ISSKIP>
    struct ContextProvider : public igloo::ContextWithAttribute<InnerContext>
  {
    typedef InnerContext IGLOO_CURRENT_CONTEXT;
    typedef InnerContext IGLOO_OUTER_CONTEXT;

    static bool IsMarkedAsOnly()
    {
      return ISONLY || detail::IsMarkedAsOnly<OuterContext>();
    }

    static bool IsMarkedAsSkip()
    {
      return ISSKIP || detail::IsContextMarkedAsSkip<OuterContext>();
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
