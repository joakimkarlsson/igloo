#include "igloo_self_test.h"
using namespace igloo;

const char* ExpectedActual = "\nActual: [ 1, 2, 3, 5, 8 ]";

template <typename T>
struct SequenceContainerTestsBase : public BaseFixture<SequenceContainerTestsBase<T> >
{
  using BaseFixture<SequenceContainerTestsBase<T> >::Is;
  using BaseFixture<SequenceContainerTestsBase<T> >::Has;
  typedef SequenceContainerTestsBase<T> IGLOO_FIXTURE_TYPE;
  
   void SetUp()
   {
      container.clear();
      container.push_back(1);
      container.push_back(2);
      container.push_back(3);
      container.push_back(5);
      container.push_back(8);
   }

   TestMethod(ShouldHandleAllOperator)
   {
       Assert::That(container, Has().All().GreaterThan(1).Or().LessThan(4));
   }

   TestMethod(ShouldHandleFailingAllOperator)
   {
      AssertTestFails(Assert::That(container, Has().All().GreaterThan(4)), std::string("Expected: all greater than 4") + ExpectedActual);
   }

   TestMethod(SHouldHandleInvalidExpressionAfterAllOperator)
   {
      AssertTestFails(Assert::That(container, Has().All().Not()), "The expression contains a not operator without any operand");
   }

   TestMethod(ShouldHandleNoExpressionAfterAllOperator)
   {
      AssertTestFails(Assert::That(container, Has().All()), "The expression after an all operator does not yield any result");
   }

   TestMethod(ShouldHandleAtLeastOperator)
   {
      Assert::That(container, Has().AtLeast(1).LessThan(5));
   }

   TestMethod(ShouldHandleFailingAtLeastOperator)
   {
      AssertTestFails(Assert::That(container, Has().AtLeast(2).LessThan(2)), std::string("Expected: at least 2 less than 2") + ExpectedActual);
   }

   TestMethod(ShouldHandleExactlyOperator)
   {
      Assert::That(container, Has().Exactly(1).EqualTo(3));
   }

   TestMethod(ShouldHandleFailingExactlyOperator)
   {
      AssertTestFails(Assert::That(container, Has().Exactly(2).EqualTo(3)), std::string("Expected: exactly 2 equal to 3") + ExpectedActual);
   }

   TestMethod(ShouldHandleAtMostOperator)
   {
      Assert::That(container, Has().AtMost(1).EqualTo(5));
   }

   TestMethod(ShouldHandleFailingAtMostOperator)
   {
      AssertTestFails(Assert::That(container, Has().AtMost(1).EqualTo(3).Or().EqualTo(5)), std::string("Expected: at most 1 equal to 3 or equal to 5") + ExpectedActual);
   }

   TestMethod(ShouldHandleNoneOperator)
   {
      Assert::That(container, Has().None().EqualTo(666));
   }

   TestMethod(ShouldHandleFailingNoneOperator)
   {
      AssertTestFails(Assert::That(container, Has().None().EqualTo(5)), std::string("Expected: none equal to 5") + ExpectedActual);
   }

  TestMethod(ShouldHandleContaining)
  {
    Assert::That(container, Contains(3));
  }

	TestMethod(ShouldDetectFailingContains)
	{
      AssertTestFails(Assert::That(container, Contains(99)), std::string("contains 99") + ExpectedActual);
	}

  TestMethod(ShouldHandleOfLength)
  {
    Assert::That(container, HasLength(5));
  }

  TestMethod(ShouldHandleFailingOfLength)
  {
     AssertTestFails(Assert::That(container, HasLength(7)), std::string("of length 7") + ExpectedActual);
  }

  TestMethod(ShouldHandleContaining_ExpressionTemplates)
  {
    Assert::That(container, Contains(3));
  }

	TestMethod(ShouldDetectFailingContains_ExpressionTemplates)
	{
      AssertTestFails(Assert::That(container, Contains(99)), std::string("contains 99") + ExpectedActual);
	}

  TestMethod(ShouldHandleOfLength_ExpressionTemplates)
  {
    Assert::That(container, HasLength(5));
  }

  TestMethod(ShouldHandleFailingOfLengthForVectors)
  {
     AssertTestFails(Assert::That(container, HasLength(7)), std::string("of length 7") + ExpectedActual);
  }

   T container;
};

DerivedFixture(VectorTests, SequenceContainerTestsBase<std::vector<int> >)
{
};

DerivedFixture(ListTests, SequenceContainerTestsBase<std::list<int> >)
{
};

DerivedFixture(DequeTests, SequenceContainerTestsBase<std::deque<int> >)
{
};
