
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_PROGRESS_OUTPUT_H
#define IGLOO_PROGRESS_OUTPUT_H

namespace igloo {

  struct ProgressOutput
  {
    virtual void PrintSuccess(const ContextBase& context, const std::string& specName) const = 0;
    virtual void PrintFailure(const ContextBase& context, const std::string& specName) const = 0;
  };

  struct DefaultProgressOutput : public ProgressOutput
  {
    virtual void PrintSuccess(const ContextBase&, const std::string&) const 
    {
      std::cout << ".";
    }

    virtual void PrintFailure(const ContextBase&, const std::string&) const
    {
      std::cout << "F";
    }
  };

  struct VerboseProgressOutput : public ProgressOutput
  {
    virtual void PrintSuccess(const ContextBase& context, const std::string& specName) const 
    {
      std::cout << "Given " << context.Name() << ", then " << specName << " is fulfilled" << std::endl;
    }

    virtual void PrintFailure(const ContextBase& context, const std::string& specName) const
    {
      std::cout << "Given " << context.Name() << ", then " << specName << " is not fulfilled" << std::endl;
    }
  };

  struct NullProgressOutput : public ProgressOutput
  {
    virtual void PrintSuccess(const ContextBase&, const std::string&) const 
    {}

    virtual void PrintFailure(const ContextBase&, const std::string&) const
    {}
  };

}

#endif
