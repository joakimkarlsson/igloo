---
layout: index
---

### Latest Version

[http://github.com/joakimkarlsson/igloo](http://github.com/joakimkarlsson/igloo)

### Releases

[https://github.com/joakimkarlsson/igloo/tags](https://github.com/joakimkarlsson/igloo/tags)

### Release Notes

####Version 1.0.0 (2013-06-26)

- Support for command line switches for selecting output format. 
- Added EqualsContainer for comparing sequence containers. 

####Version 0.9 (2012-08-28)

- Added support for XUnit XML output format. 
- Added EqualsWithDelta constraint. 
-Unknown exceptions are now caught and added to the test result. Otherwise Igloo will display a dialog on some operating systems. Igloo should now play nicer with continuous integration servers.

####Version 0.8 (2012-11-28)

- Added support for context wide set up and tear down. 
- Added support for test listeners. 

####Version 0.7 (2011-07-30)

- Added support for Visual Studio formatted output (use AssertThat instead of Assert::That to include line numbers of failing tests). 
- Added support for custom matchers via Assert::That(42, Fulfills(IsEvenNumber())); 

####Version 0.6 (2011-01-23))

- Support for Describe/It and When/Then syntax by using #include %lt;igloo/igloo_alt.h&gt;
- Added IsEmpty() and Is().Empty() container constraints

####Version 0.5 (2010-10-19)

- Support for assertions on exceptions.

####Version 0.4.2 (2010-06-10)

- Added missing include of &lt;memory&gt;.
- Aliases for registration macros moved to its own file to enable customization.

####Version 0.4.1 (2010-03-29)

- Fixed: The registration of nested contexts could fail under some circumstances.

####Version 0.4 (2010-03-19)

- Support for BDD-style tests using Context/Spec. This replaces the TestFixture/TestMethod keywords. Old terminology still supported for backwards compatibility.
- Support for nested contexts.
- A string containing multiple lines can be treated as a collection of lines by the collection constraints.
- A new context is created before each call to SetUp/Spec/TearDown to ensure that a fresh context is used in each spec.

####Version 0.3 (2010-02-16)

First public release
