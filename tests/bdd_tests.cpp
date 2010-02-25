#include <tests/igloo_self_test.h>
using namespace igloo;

struct Fuzzbox
{
  void SetMode(int mode)
  {
    std::cout << "Fuzzbox::SetMode " << mode << std::endl;
    mode_ = mode;
  }
  
  int mode_;
};

Context(IHaveAFuzzbox)
{
  Context(FuzzboxIsInCleanMode)
  {
    void SetUp()
    {
      std::cout << "FuzzboxIsInCleanMode::SetUp" << std::endl;
      fuzzbox.SetMode(32);
    }
    
    Spec(WhenIFretTheStringsTheSoundIsClean, FuzzboxIsInCleanMode)
    {
      std::cout << "WhenIFretTheStringsTheSoundIsClean " << fuzzbox.mode_ << std::endl;
    }
  };
  
  Spec(ANewFuzzBoxIsInCleanMode, IHaveAFuzzbox)
  {
    std::cout << "ANewFuzzBoxIsInCleanMode " << fuzzbox.mode_ << std::endl;
  }
  
  Fuzzbox fuzzbox;
};


