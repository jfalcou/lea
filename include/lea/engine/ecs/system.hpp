//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <lea/engine/ecs/entity.hpp>
#include <lea/engine/ecs/typename.hpp>
#include <lea/engine/ecs/component.hpp>
#include <string_view>
#include <memory>
#include <set>

namespace lea
{
  struct coordinator;

  //================================================================================================
  // Basic layout for system class
  //================================================================================================
  struct coordinator;

  struct system
  {
    system(coordinator* cc) : manager(cc) {}
    std::set<entity>  entities;
    coordinator*      manager;
  };

  //================================================================================================
  // System manager
  //================================================================================================
  struct system_manager
  {
    template<typename T> T* accept(coordinator* c)
    {
      std::string_view type_id = typename_<T>;

      assert(systems_.find(type_id) == systems_.end() && "Registering system more than once.");

      auto system = std::make_unique<T>(c);
      auto ptr    = system.get();

      systems_.insert({type_id, std::move(system)});

      return ptr;
    }

    template<typename T> void set_signature(signature s)
    {
      std::string_view type_id = typename_<T>;
      assert(systems_.find(type_id) != systems_.end() && "System used before registered.");

      signatures_.insert({type_id, s});
    }

    void on_destroy(entity e)
    {
      for (auto const& pair : systems_)
      {
        auto const& system = pair.second;
        system->entities.erase(e);
      }
    }

    void on_signature_change(entity e, signature s)
    {
      // Notify each system that an entity's signature changed
      for (auto const& pair : systems_)
      {
        auto const& [type,system]     = pair;
        auto const& system_signature  = signatures_[type];

        if ((s & system_signature) == system_signature) system->entities.insert(e);
        else                                            system->entities.erase(e);
      }
    }

    private:
    std::unordered_map<std::string_view, signature>                signatures_{};
    std::unordered_map<std::string_view, std::unique_ptr<system>>  systems_{};
  };
}
