//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <lea/3rd_party/sol.hpp>
#include <lea/api.hpp>

namespace lea
{
  struct LEA_API interpreter
  {
    interpreter();
    interpreter(char const* filename);
    void run(char const*);

    decltype(auto)  operator[](char const* id)  const { return state_[id]; }
    decltype(auto)  operator[](char const* id)        { return state_[id]; }

    private:
    sol::state                    state_;
  };
}
