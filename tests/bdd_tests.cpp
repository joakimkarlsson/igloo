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

//Context(IHaveAFuzzbox)
struct IHaveAFuzzbox;
struct ContextRegistrarIHaveAFuzzbox
{
  ContextRegistrarIHaveAFuzzbox()
  {
    igloo::TestRunner::RegisterTestFixture<igloo::TestFixtureRunner<void, IHaveAFuzzbox> >("IHaveAFuzzbox");
  }
} IHaveAFuzzboxIglooRegistrar;
struct IHaveAFuzzbox : public ContextBridge<IHaveAFuzzbox, IGLOO_CURRENT_CONTEXT>
{
  void SetUp()
  {
    std::cout << "IHaveAFuzzbox::SetUp" << std::endl;
  }
  
  //Context(FuzzboxIsInCleanMode)
  struct FuzzboxIsInCleanMode; 
  struct ContextRegistrarFuzzboxIsInCleanMode 
  { 
    ContextRegistrarFuzzboxIsInCleanMode() 
    { 
      igloo::TestRunner::RegisterTestFixture<igloo::TestFixtureRunner<void, FuzzboxIsInCleanMode> >("FuzzboxIsInCleanMode"); 
    } 
  } FuzzboxIsInCleanModeIglooRegistrar; 
  
  struct FuzzboxIsInCleanMode : public ContextBridge<FuzzboxIsInCleanMode, IGLOO_CURRENT_CONTEXT>
  {
    FuzzboxIsInCleanMode()
    {
      std::cout << "FuzzBoxIsInCleanMode. Context " << typeid(IGLOO_CURRENT_CONTEXT).name() << std::endl;
    }
    
    void SetUp()
    {
      std::cout << "FuzzboxIsInCleanMode::SetUp" << std::endl;
      Parent().fuzzbox.SetMode(32);
    }
    
    struct SpecRegistrarWhenIFretTheStringsTheSoundIsClean 
    { 
      SpecRegistrarWhenIFretTheStringsTheSoundIsClean() 
      { 
        BaseFixture<IGLOO_CURRENT_CONTEXT>::RegisterTestMethod("WhenIFretTheStringsTheSoundIsClean", &IGLOO_CURRENT_CONTEXT::WhenIFretTheStringsTheSoundIsClean); 
      } 
    } SpecRegistrarWhenIFretTheStringsTheSoundIsCleanRegistrar; 

    virtual void WhenIFretTheStringsTheSoundIsClean()    
    {
      std::cout << "WhenIFretTheStringsTheSoundIsClean " << Parent().fuzzbox.mode_ << std::endl;
    }
  };
  
  //Spec(ANewFuzzBoxIsInCleanMode, IHaveAFuzzbox)
  struct SpecRegistrarANewFuzzBoxIsInCleanMode 
  { 
    SpecRegistrarANewFuzzBoxIsInCleanMode() 
    { 
      std::cout << "Registering method for context: " << typeid(IGLOO_CURRENT_CONTEXT).name() << std::endl;
      BaseFixture<IGLOO_CURRENT_CONTEXT>::RegisterTestMethod("ANewFuzzBoxIsInCleanMode", &IGLOO_CURRENT_CONTEXT::ANewFuzzBoxIsInCleanMode); 
    } 
  } SpecRegistrarANewFuzzBoxIsInCleanMode; 
  
  virtual void ANewFuzzBoxIsInCleanMode()      
  {
    std::cout << "ANewFuzzBoxIsInCleanMode " << fuzzbox.mode_ << std::endl;
  }
  
  Fuzzbox fuzzbox;
};


