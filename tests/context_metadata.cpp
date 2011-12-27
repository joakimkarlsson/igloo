
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;


Context(A_context_with_metadata)
{
  struct ContextHavingMetaData : public ContextProvider<ContextHavingMetaData, ContextWithMetaData<void> >
  {
    ContextAttribute("name of metadata", "value of metadata")

  } context_having_metadata;

  Spec(MetaData_can_be_retrieved)
  {
    const std::string& string_metadata = context_having_metadata.GetMetaData("name of metadata");

    AssertThat(string_metadata, Is().EqualTo("value of metadata"));
  }

  Spec(empty_string_is_returned_if_metadata_doesnt_exists)
  {
    const std::string& metadata = context_having_metadata.GetMetaData("non-existing metadata");

    AssertThat(metadata, Is().Empty());
  }
};
