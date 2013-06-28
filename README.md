igloo
=====

A framework for unit testing in C++

Igloo is a unit testing framework for C++ that aims to:

* stay out of your way and let you focus on what you want to test
* help you create readable tests
* have a syntax that doesn’t make you repeat yourself

For more info visit http://igloo-testing.org/

## Example

The following is a complete test application written in Igloo

```C++
#include <igloo/igloo_alt.h>
using namespace igloo;

Describe(a_guitar_with_a_fuzzbox)
{
  void SetUp()
  {
    guitar.AddEffect(fuzzbox);
  }

  It(starts_in_clean_mode)
  {
    Assert::That(guitar.Sound(), Equals(Clean));
  }

  Describe(in_distorted_mode)
  {
    void SetUp()
    {
      Parent().fuzzbox.Switch();
    }

    It(sounds_distorted)
    {
      Assert::That(Parent().guitar.Sound(), Equals(Distorted));
    }

    It(sounds_clean_when_I_switch_the_fuzzbox)
    {
      Parent().fuzzbox.Switch();
      Assert::That(Parent().guitar.Sound(), Equals(Clean));
    }
  };

  Fuzzbox fuzzbox;
  Guitar guitar;
};

int main(int argc, const char *argv[])
{
  return TestRunner::RunAllTests(argc, argv);
}
```

