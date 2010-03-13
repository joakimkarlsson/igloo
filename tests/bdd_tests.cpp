#include <tests/igloo_self_test.h>
using namespace igloo;

struct Fuzzbox
{
  enum Mode
  {
    Clean,
    Distorted
  };
  
  void SetMode(Mode mode)
  {
    mode_ = mode;
  }
  
  Mode GetMode()
  {
    return mode_;
  }
  
private:
  Mode mode_;
};

Context(IHaveAFuzzbox)
{
  void SetUp()
  {
    fuzzbox.SetMode(Fuzzbox::Clean);
  }
  
  Spec(ANewFuzzBoxIsInCleanMode)
  {
    Assert::That(fuzzbox.GetMode(), Equals(Fuzzbox::Clean));
  }  
  
  Context(FuzzboxIsInDistortedMode)
  {
    void SetUp()
    {
      Parent().fuzzbox.SetMode(Fuzzbox::Distorted);
    }
    
    Spec(WhenIFretTheStringsTheSoundIsDistorted)
    {
      Assert::That(Parent().fuzzbox.GetMode(), Equals(Fuzzbox::Distorted));
    }
  };
  
  Fuzzbox fuzzbox;
};


