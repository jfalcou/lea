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
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <array>
#include <string_view>

namespace lea
{
  struct opaque_storage
  {
    virtual ~opaque_storage() = default;
    virtual void on_destroy(entity e) = 0;
  };

  //================================================================================================
  // Provide a type-erased storage system for component with
  //================================================================================================
  template<typename T>
  struct component_storage : public opaque_storage
  {
    void insert(entity e, T component)
    {
      assert(   entity_index_.find(e) == entity_index_.end()
            &&  "Component added to a given entity more than once."
            );

      std::size_t fresh_index     = size_;
      entity_index_[e]            = fresh_index;
      index_entity_[fresh_index]  = e;
      components_[fresh_index]    = component;
      ++size_;
    }

    void remove(entity e)
    {
      assert(entity_index_.find(e) != entity_index_.end() && "Removing non-existent component.");

      // Copy element at end into deleted element's place to maintain density
      std::size_t removed_index  = entity_index_[e];
      std::size_t last_index     = size_ - 1;
      components_[removed_index] = components_[last_index];

      // Update map to point to moved spot
      entity last_entity            = index_entity_[last_index];
      entity_index_[last_entity]    = removed_index;
      index_entity_[removed_index]  = last_entity;

      entity_index_.erase(e);
      index_entity_.erase(last_index);

      --size_;
    }

    T& get(entity e)
    {
      assert(entity_index_.find(e) != entity_index_.end() && "Retrieving non-existent component.");
      return components_[entity_index_[e]];
    }

    void on_destroy(entity e) override
    {
      if (entity_index_.find(e) != entity_index_.end())
      {
        remove(e);
      }
    }

    private:
    // Packed array of all existing entities
    std::array<T, last_valid_entity> components_;

    // Access entity from ID and ID from entity
    std::unordered_map<entity, std::size_t> entity_index_;
    std::unordered_map<std::size_t, entity> index_entity_;

    // Total size of valid entries in the array.
    std::size_t size_;
  };

  //================================================================================================
  // Manage lifetime and association of components with entities
  //================================================================================================
  struct component_manager
  {
    template<typename T> void activate()
    {
      std::string_view type_id = typename_<T>;

      assert(   types_map_.find(type_id) == types_map_.end()
            &&  "Registering component type more than once."
            );

      // Register the type in the type map
      types_map_.insert({type_id, next_type_});

      // Allocate storage for this component
      storage_map_.insert({type_id, std::make_unique<component_storage<T>>()});
      ++next_type_;
    }

    template<typename T> component_type type_of()
    {
      std::string_view type_id = typename_<T>;
      assert(types_map_.find(type_id) != types_map_.end() && "Component not registered before use.");
      return types_map_[type_id];
    }

    template<typename T> void add(entity e, T component)  { get_array<T>()->insert(e, component); }
    template<typename T> void remove(entity e)            { get_array<T>()->remove(e);            }
    template<typename T> T&   component(entity e)         { return get_array<T>()->get(e);        }

    void on_destroy(entity e)
    {
      for (auto const& pair : storage_map_)
      {
        auto const& component = pair.second;
        component->on_destroy(e);
      }
    }

  private:
    // Map from type string pointer to a component type
    std::unordered_map<std::string_view, component_type> types_map_{};

    // Map from type string pointer to a component array
    std::unordered_map<std::string_view, std::unique_ptr<opaque_storage>> storage_map_{};

    // The component type to be assigned to the next registered component - starting at 0
    component_type next_type_{};

    // Convenience function to get the statically casted pointer to the component_storage of type T.
    template<typename T> component_storage<T>* get_array()
    {
      std::string_view type_id = typename_<T>;

      assert(types_map_.find(type_id) != types_map_.end() && "Component not registered before use.");

      auto ptr = storage_map_[type_id].get();
      return static_cast<component_storage<T>*>(ptr);
    }
  };
}
