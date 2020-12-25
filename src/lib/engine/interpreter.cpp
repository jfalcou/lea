//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/interpreter.hpp>

namespace lea
{
  interpreter::interpreter()
  {
    state_.open_libraries ( sol::lib::base  , sol::lib::io
                          , sol::lib::table , sol::lib::string
                          , sol::lib::math
                          );
  }

  interpreter::interpreter(char const* filename) : interpreter()
  {
    run(filename);
  }

  void interpreter::run(char const* filename)
  {
    state_.script_file( filename );
  }
}
