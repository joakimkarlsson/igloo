#ifndef IGLOO_TESTS_FAKES_CONTEXT_RUNNER_H
#define IGLOO_TESTS_FAKES_CONTEXT_RUNNER_H

namespace igloo { namespace fakes {

  class FakeContextRunner : public BaseContextRunner
  {
    public:
      FakeContextRunner(const std::string& contextName, const char* fileName, int lineNumber) 
        : BaseContextRunner(contextName, fileName, lineNumber), is_only_(false), is_skip_(false) {}

      virtual void RunContext(TestResults& results, TestListener&) const
      {
        std::stringstream stm;
        stm << "RunContext called" << std::endl;
        callLog += stm.str();

        TestResultFactory factory(ContextName(), "SpecName");
        results.AddResult(factory.CreateSuccessful());
      }

      virtual bool IsContextMarkedAsOnly() const
      {
        return is_only_;
      }

      virtual bool IsMarkedAsSkip() const
      {
        return is_skip_;
      }

      void MarkAsOnly()
      {
        is_only_ = true;
      }

      void MarkAsSkip()
      {
        is_skip_ = true;
      }

      bool is_only_;
      bool is_skip_;
      mutable std::string callLog;
  };


} }

#endif
