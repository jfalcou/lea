//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/math/random.hpp>
#include <cstdlib>
#include <chrono>

namespace lea
{
  std::mt19937 random::random_engine_ = {};
  sol::table   random::bindings_;

  void  random::setup(interpreter& st)
  {
    // Initialize random seed
    int s = st["settings"]["seed"].get<std::uint64_t>();
    auto tictoc = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    seed( (s != -1) ? s : static_cast<std::uint64_t>(tictoc) );

    // Export LUA bindings for random functions
    bindings_ = st["math"].force();
    bindings_.set_function( "flip"  , &random::flip );
    bindings_.set_function( "roll"  , [](int   mn, int   mx) { return  random::roll(mn,mx); } );
    bindings_.set_function( "sample", [](float mn, float mx) { return  random::roll(mn,mx); } );
  }

  void  random::seed(std::uint64_t s)
  {
    random_engine_.seed(s);
  }

  bool  random::flip()
  {
    return roll(0,1) == 0;
  }

  int   random::roll(int mn, int mx)
  {
    std::uniform_int_distribution<> distribution(mn, mx);
    return distribution(random_engine_);
  }

  float random::roll(float mn, float mx)
  {
    std::uniform_real_distribution<float> distribution(mn, mx);
    return distribution(random_engine_);
  }
}
