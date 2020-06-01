//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <memory>

namespace lea
{
  // Monomorphic value_ptr
  template<typename T> struct value_ptr
  {
    value_ptr()                         = default;
    value_ptr(value_ptr &&)             = default;
    value_ptr& operator=(value_ptr &&)  = default;

    ~value_ptr() = default;

    value_ptr(value_ptr const& o) : storage_(new T{*o})
    {
    }

    value_ptr& operator=(value_ptr const& o)
    {
      value_ptr that(o);
      storage_.swap(that.storage_);
      return *this;
    }

    value_ptr(T const& o) : storage_(new T{o}) {}
    value_ptr(T&&      o) : storage_(new T{std::move(o)}) {}

    inline void swap(value_ptr& o)  noexcept
    {
      storage_.swap(o.storage_);
    }

    decltype(auto) operator*()        noexcept { return *storage_; }
    decltype(auto) operator*() const  noexcept { return *storage_; }

    decltype(auto) operator->()        noexcept { return storage_.get(); }
    decltype(auto) operator->() const  noexcept { return storage_.get(); }

    std::unique_ptr<T> storage_;
  };

  template<typename T> inline void swap(value_ptr<T>& a,value_ptr<T>& b) noexcept
  {
    a.swap(b);
  }
}
