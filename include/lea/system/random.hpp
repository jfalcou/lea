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
  struct LEA_API random
  {
    void   seed(std::uint64_t);
    bool   flip();
    int    roll(int, int);
    float  sample(float, float);

    random(interpreter&);

    private:
    std::mt19937 random_engine_;
    sol::table   bindings_;
  };
}
