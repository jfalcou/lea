//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <lea/api.hpp>
#include <filesystem>

namespace lea
{
  LEA_API std::filesystem::path get_current_directory();
  LEA_API std::filesystem::path get_config(const char* filename);
}
