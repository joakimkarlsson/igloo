#ifndef IGLOO_TESTFIXTURE_H
#define IGLOO_TESTFIXTURE_H

#include "assertionexception.h"
#include "assert.h"
#include "testresult.h"
#include "syntax.h"

namespace igloo {

  struct TestFixtureBase
  {
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    RootNode Is()
    {
      RootNode node;
      return node;
    }
    
    typedef ConstraintList<Noop, Nil> EmptyConstraintList;
    
    ExpressionBuilder<EmptyConstraintList> Iz()
    {
      return EmptyConstraintList(Noop(), Nil());
    }
  };
  
  template <typename FixtureType>
  struct TestFixture : public TestFixtureBase 
  {
    typedef FixtureType IGLOO_FIXTURE_TYPE;
  };  
}

#endif // IGLOO_TESTFIXTURE_H
