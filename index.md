---
layout: index
---

Igloo is a unit testing framework for C++ that aims to:

- stay out of your way and let you focus on what you want to test
- help you create readable tests
- have a syntax that doesn’t make you repeat yourself

#License

Igloo is distributed under the [Boost Software License, Version 1.0](http://www.boost.org/users/license.html), which encourages both commercial and non-commercial use.

#Example

The following listing shows a complete test application written in Igloo:

{% highlight cpp %}
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

int main(int argv, const *char[] argv)
{
  return TestRunner::RunAllTests(argc, argv);
}
{% endhighlight %}

## Screencast

The following video shows Igloo being used as the testing framework to create one possible solution to the Conway’s Game of Life TDD Kata.

<div class='embed-vimeo' style='text-align:center;'>
  <iframe src='http://player.vimeo.com/video/18350401' width='400' height='225' frameborder='0'> </iframe>
</div>
<p><a href="http://vimeo.com/18350401">C++ TDD Kata: Conway&#8217;s Game of Life</a> from <a href="http://vimeo.com/user5608696">Joakim Karlsson</a> on <a href="http://vimeo.com">Vimeo</a>.</p>


## Installing Igloo
Igloo is implemented as a set of header files. Therefore there is no need for you to go through any additional steps to build it. After you’ve downloaded Igloo, just tell your build system to look for additional header files in the directory where you put Igloo, and you’re ready to go.
