#include <tests/igloo_self_test.h>
using namespace igloo;

namespace igloo_example {
  struct Fuzzbox
  { 
    bool on_;
    
    Fuzzbox() : on_(false) 
    {
    }
    
    void Switch()
    {
      on_ = !on_;
    }
    
  };
  
  typedef enum
  {
    Clean,
    Distorted
  } Sounds;
  
  struct Guitar
  {
    Fuzzbox* fuzzbox_;
    
    void AddEffect(Fuzzbox& fuzzbox)
    {
      fuzzbox_ = &fuzzbox;
    }
    
    Sounds Sound()
    {
      return fuzzbox_->on_ ? Distorted : Clean;
    }
  };
  
  Context(AGuitarWithAFuzzbox)
  {
    void SetUp()
    {
      guitar.AddEffect(fuzzbox);
    }
    
    Spec(FuzzboxStartsInCleanMode)
    {
      Assert::That(guitar.Sound(), Equals(Clean));
    }  
    
    Context(FuzzboxIsInDistortedMode)
    {
      void SetUp()
      {
        Parent().fuzzbox.Switch();
      }
      
      Spec(WhenIFretTheStringsTheSoundIsDistorted)
      {
        Assert::That(Parent().guitar.Sound(), Equals(Distorted));
      }
      
      Spec(WhenISwitchTheFuzzboxTheSoundIsClean)
      {
        Parent().fuzzbox.Switch();
        Assert::That(Parent().guitar.Sound(), Equals(Clean));
      }
    };
    
    Fuzzbox fuzzbox;
    Guitar guitar;
  };
  
}
