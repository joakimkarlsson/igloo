
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_CONTEXT_H
#define IGLOO_CONTEXT_H

#include <igloo/core/assertionexception.h>
#include <igloo/core/assert.h>
#include <igloo/core/testresult.h>
#include <igloo/core/context.h>

namespace igloo {

  template <typename ContextType>
    struct ContextMetaData
    {
      static void Set(const std::string name, std::string value)
      {
        metaDataContainer()[name] = value;
      }

      static const std::string& Get(const std::string& name)
      {
        return metaDataContainer()[name];
      }

      private:

      static std::map<std::string, std::string>& metaDataContainer()
      {
        static std::map<std::string, std::string> metaDataContainer;
        return metaDataContainer;
      }
    };

    template <typename ContextType>
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

      void SetMetaData(const std::string& name, const char* value) const
      {
        ContextMetaData<ContextType>::Set(name, value);
      }

      const std::string& GetMetaData(const std::string& name) const
      {
        return ContextMetaData<ContextType>::Get(name);
      }

      private:
      std::string m_name;
    };

}

#endif
