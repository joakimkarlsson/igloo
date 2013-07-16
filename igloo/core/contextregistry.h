
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_CONTEXTREGISTRY_H
#define IGLOO_CONTEXTREGISTRY_H

namespace igloo {

  template <typename ContextToCall>
  class ContextRegistry  
  {
    typedef void (ContextToCall::*SpecPtr)();
    struct SpecInfo
    {
      SpecPtr spec_ptr;
      bool skip;
      bool only;
    };
    typedef std::pair<std::string, SpecInfo> NamedSpec;
    typedef std::map<std::string, SpecInfo> Specs;

    public:
    static void RegisterSpec(const std::string& name, void (ContextToCall::*spec)(), bool skip = false, bool only = false)
    {
      SpecInfo spec_info;
      spec_info.spec_ptr = spec;
      spec_info.skip = skip;
      spec_info.only = only;
      GetSpecs().insert(std::make_pair(name, spec_info));
    }

    static void ClearRegisteredSpecs()
    {
      GetSpecs().clear();
    }

    template <typename ContextToCreate>
      static void Run(const std::string& contextName, TestResults& results, TestListener& testListener)
      {    
        Specs specs;
        GetSpecsToRun(specs);
        CallSpecs<ContextToCreate>(specs, contextName, results, testListener);
      }


    template <typename ContextToCreate>
      static void CallSpecs(const Specs& specs, const std::string& contextName, TestResults& results, TestListener& testListener)
      {
        ContextToCreate::SetUpContext();

        ContextToCreate c;
        c.SetName(contextName);

        testListener.ContextRunStarting(c);

        typename Specs::const_iterator it;
        for (it = specs.begin(); it != specs.end(); it++)
        {
          const std::string& specName = (*it).first;
          SpecInfo spec_info = (*it).second;

          ContextToCreate context;
          context.SetName(contextName);

          testListener.SpecRunStarting(context, specName);

          if(!spec_info.skip)
          {
            if(CallSpec(context, specName, spec_info.spec_ptr, results))
            {
              testListener.SpecSucceeded(context, specName); 
            }
            else
            {
              testListener.SpecFailed(context, specName);
            }
          }
        }

        ContextToCreate::TearDownContext();

        testListener.ContextRunEnded(c);
      }

    static bool CallSpec(ContextToCall& context, const std::string& specName, SpecPtr spec, TestResults& results)
    {
      bool result = true;

      try
      {
        context.IglooFrameworkSetUp();
        (context.*spec)();
      }
      catch (const snowhouse::AssertionException& e)
      {
        results.AddResult(TestResultFactory(context.Name(), specName).CreateFromException(e));
        result = false;
      }
      catch (...)
      {
        results.AddResult(FailedTestResult(context.Name(), specName, "Caught unknown exception"));
        result = false;
      }

      try 
      {
        context.IglooFrameworkTearDown();
      }
      catch (const snowhouse::AssertionException& e) 
      {
        results.AddResult(TestResultFactory(context.Name(), specName).CreateFromException(e));
        result = false;
      }
      catch (...)
      {
        results.AddResult(FailedTestResult(context.Name(), specName, "Caught unknown exception"));
        result = false;
      }

      if(result)
      {
        results.AddResult(TestResultFactory(context.Name(), specName).CreateSuccessful());
      }

      return result;
    }

    static Specs& GetSpecs()
    {
      static Specs specs;
      return specs;
    }

    static bool is_spec_not_marked_as_only(const NamedSpec& spec)
    {
      return !is_spec_marked_as_only(spec);
    }

    static bool is_spec_marked_as_only(const NamedSpec& spec)
    {
      return spec.second.only;
    }

    static void GetSpecsMarkedAsOnly(Specs& specs)
    {
      std::remove_copy_if(GetSpecs().begin(), GetSpecs().end(), std::inserter(specs, specs.end()), is_spec_not_marked_as_only);
    }

    static bool HasSpecsMarkedAsOnly()
    {
      return std::find_if(GetSpecs().begin(), GetSpecs().end(), is_spec_marked_as_only) != GetSpecs().end();
    }

    static void GetSpecsToRun(Specs& specs)
    {
      if(HasSpecsMarkedAsOnly())
      {
        GetSpecsMarkedAsOnly(specs);
      }
      else
      {
        std::copy(GetSpecs().begin(), GetSpecs().end(), std::inserter(specs, specs.end()));
      }
    }
  };  
}
#endif
