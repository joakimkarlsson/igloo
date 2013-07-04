#ifndef IGLOO_TESTS_FAKES_CONTEXT_RUNNER_H
#define IGLOO_TESTS_FAKES_CONTEXT_RUNNER_H

namespace igloo { namespace fakes {

  class FakeContextRunner : public BaseContextRunner
  {
    public:
      FakeContextRunner(const std::string& contextName) : BaseContextRunner(contextName), is_only_(false) {}

      virtual void RunContext(TestResults& results, TestListener&) const
      {
        std::stringstream stm;
        stm << "RunContext for '" << ContextName() << "' called" << std::endl;
        callLog += stm.str();

        TestResultFactory factory(ContextName(), "SpecName");
        results.AddResult(factory.CreateSuccessful());
      }

      virtual bool IsOnly() const
      {
        return is_only_;
      }

      void MarkAsOnly()
      {
        is_only_ = true;
      }

      bool is_only_;
      mutable std::string callLog;
  };


} }

#endif
