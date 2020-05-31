//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <lea/engine/interpreter.hpp>
#include <lea/3rd_party/sol.hpp>
#include <lea/api.hpp>
#include <random>

namespace lea
{
  struct random
  {
    LEA_API static void   seed(std::uint64_t);
    LEA_API static bool   flip();
    LEA_API static int    roll(int, int);
    LEA_API static float  roll(float, float);

    LEA_API static void  setup(interpreter&);

    static std::mt19937 random_engine_;
    static sol::table   bindings_;
  };
}
