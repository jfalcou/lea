//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <string_view>

namespace lea
{
  template<typename T> struct type_name_
  {
    static constexpr auto value() noexcept
    {
  #if defined(_MSC_VER )
      std::string_view data(__FUNCSIG__);
      auto i = data.find('<') + 1, j = data.find(">::value");
      return data.substr(i, j - i);
  #else
      std::string_view data(__PRETTY_FUNCTION__);
      auto i = data.find('=') + 2, j = data.find_last_of(']');
      return data.substr(i, j - i);
  #endif
    }
  };

  template<typename T>
  inline constexpr auto const typename_ = type_name_<T>::value();
}
