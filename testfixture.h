#ifndef IGLOO_TESTFIXTURE_H
#define IGLOO_TESTFIXTURE_H

#include "assertionexception.h"
#include "assert.h"
#include "testresult.h"

namespace igloo {

  struct TestFixtureBase
  {
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
       
    ExpressionBuilder<Nil> Is()
    {
      return ExpressionBuilder<Nil>(Nil());
    }

    ExpressionBuilder<Nil> Has()
    {
       return ExpressionBuilder<Nil>(Nil());
    }
  };
  
  template <typename FixtureType>
  struct TestFixture : public TestFixtureBase 
  {
    typedef FixtureType IGLOO_FIXTURE_TYPE;
  };  
}

#endif // IGLOO_TESTFIXTURE_H
