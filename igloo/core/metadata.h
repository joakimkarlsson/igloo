
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_METADATA_H
#define IGLOO_METADATA_H

namespace igloo {
  struct MetaData
  {
    virtual const std::string& GetMetaData(const std::string& name) const = 0;
  };
}

#endif
