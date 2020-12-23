//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <bitset>
#include <cstdint>
#include <queue>
#include <array>
#include <cassert>

namespace lea
{
  struct coordinator;

  //================================================================================================
  // Basic types & constants
  //================================================================================================
  // An entity is basically just an ID for later
  using entity = std::uint64_t;

  // Defines a component type
  using component_type = std::uint8_t;

  // Some configurations constant
  inline constexpr entity         last_valid_entity     = 1'024'000;
  inline constexpr component_type last_valid_component  = 64;

  //================================================================================================
  // Signature
  //================================================================================================
  // Defines the components' signature of an entity
  using signature = std::bitset<last_valid_component>;

  //================================================================================================
  // Manage the creation and setup of entities
  //================================================================================================
  struct entity_manager
  {
    entity_manager()
    {
      for(entity e = 0; e < last_valid_entity; ++e)
        entities_.push(e);
    }

    entity create()
    {
      assert(count_ < last_valid_entity && "Too many entities in existence.");

      entity id = entities_.front();
      entities_.pop();
      ++count_;

      return id;
    }

    void destroy(entity e)
    {
      assert(e < last_valid_entity && "entity out of range.");

      signatures_[e].reset();
      entities_.push(e);
      --count_;
    }

    void set_signature(entity entity, signature signature)
    {
      assert(entity < last_valid_entity && "entity out of range.");
      signatures_[entity] = signature;
    }

    signature get_signature(entity entity)
    {
      assert(entity < last_valid_entity && "entity out of range.");
      return signatures_[entity];
    }

    private:
    std::queue<entity> entities_{};
    std::array<signature, last_valid_entity> signatures_{};
    std::size_t count_{};
  };
}
