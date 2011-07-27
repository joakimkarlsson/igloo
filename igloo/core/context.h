
//          Copyright Joakim Karlsson & Kim Gräsman 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_CONTEXT_H
#define IGLOO_CONTEXT_H

#include <igloo/core/assertionexception.h>
#include <igloo/core/assert.h>
#include <igloo/core/testresult.h>

namespace igloo {

  struct ContextBase 
  {
      virtual ~ContextBase() {}
      
      virtual void IglooFrameworkSetUp()
      {}
      
      virtual void IglooFrameworkTearDown()
      {}
      
      virtual void SetUp()
      {
      }

      virtual void TearDown()
      {
      }

      void SetName(const std::string& name)
      {
        m_name = name;
      }

      std::string Name() const
      {
        return m_name;
      }

    private:
      std::string m_name;
  };
  
}

#endif
