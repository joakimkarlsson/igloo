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
  void SetUp()
  {
    std::cout << "IHaveAFuzzbox::SetUp" << std::endl;
  }
  
  Context(FuzzboxIsInCleanMode)
  {
    void SetUp()
    {
      std::cout << "FuzzboxIsInCleanMode::SetUp" << std::endl;
      Parent().fuzzbox.SetMode(32);
    }
    
    Spec(WhenIFretTheStringsTheSoundIsClean)
    {
      std::cout << "WhenIFretTheStringsTheSoundIsClean " << Parent().fuzzbox.mode_ << std::endl;
    }
  };
  
  Spec(ANewFuzzBoxIsInCleanMode)
  {
    std::cout << "ANewFuzzBoxIsInCleanMode " << fuzzbox.mode_ << std::endl;
  }
  
  Fuzzbox fuzzbox;
};


