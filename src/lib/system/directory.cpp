//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/system/directory.hpp>
#include <filesystem>
#include <unistd.h>
#include <memory>

namespace lea
{
  std::filesystem::path get_current_directory()
  {
    std::unique_ptr<char, void(*)(void*)> w { get_current_dir_name(), std::free };
    std::filesystem::path that(w.get());
    return that;
  }

  std::filesystem::path get_config(const char* filename)
  {
    auto base = get_current_directory();

    if( auto p = base / filename; std::filesystem::exists( p ) )
    {
      return p;
    }
    else if( auto p = (base / "../") / filename; std::filesystem::exists( p ) )
    {
      return p;
    }
    else
    {
      return p;
    }
  }
}
