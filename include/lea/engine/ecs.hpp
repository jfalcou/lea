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
#include <lea/engine/ecs/component.hpp>
#include <lea/engine/ecs/system.hpp>
#include <memory>
#include <tuple>

namespace lea
{
  //================================================================================================
  // ECS global manager
  //================================================================================================
  struct coordinator
  {
    coordinator() : components_(std::make_unique<component_manager>())
                  , entities_(std::make_unique<entity_manager>())
                  , systems_(std::make_unique<system_manager>())
    {}

    // Entity
    entity create() { return entities_->create(); }

    void destroy(entity e)
    {
      entities_->destroy(e);
      components_->on_destroy(e);
      systems_->on_destroy(e);
    }

    template<typename... Ts> entity create(Ts... component)
    {
      auto e = entities_->create();
      (components_->add<Ts>(e, component),...);

      auto signature = entities_->get_signature(e);
      (signature.set(components_->type_of<Ts>(), true),...);
      entities_->set_signature(e, signature);

      systems_->on_signature_change(e, signature);
      return e;
    }

    // Component
    template<typename... Ts>  void activate()           { (components_->activate<Ts>(),...);    }
    template<typename T>      auto type_of()            { return components_->type_of<T>();     }
    template<typename T>      T&   component(entity e)  { return components_->component<T>(e);  }

    template<typename T, typename U, typename... Ts> auto component(entity e)
    {
      return std::tie( components_->component<T>(e)
                     , components_->component<U>(e)
                     , components_->component<Ts>(e)...
                     );
    }


    template<typename... Ts> void add(entity e, Ts... component)
    {
      (components_->add<Ts>(e, component),...);

      auto signature = entities_->get_signature(e);
      (signature.set(components_->type_of<Ts>(), true),...);
      entities_->set_signature(e, signature);

      systems_->on_signature_change(e, signature);
    }

    template<typename... Ts> void remove(entity e)
    {
      (components_->remove<Ts>(e),...);

      auto signature = entities_->get_signature(e);
      (signature.set(components_->type_of<Ts>(), false),...);
      entities_->set_signature(e, signature);

      systems_->on_signature_change(e, signature);
    }

    // System
    template<typename T> void set_signature(signature s)  { systems_->set_signature<T>(s);    }
    template<typename T> auto accept()                    { return systems_->accept<T>(this); }

    template<typename T, typename U, typename... Ts> auto accept()
    {
      return std::make_tuple( systems_->accept<T>(this)
                            , systems_->accept<U>(this)
                            , systems_->accept<Ts>(this)...
                            );
    }

    private:
    std::unique_ptr<component_manager>  components_;
    std::unique_ptr<entity_manager>     entities_;
    std::unique_ptr<system_manager>     systems_;
  };

  //================================================================================================
  // Helpers
  //================================================================================================
  template<typename... Ts>
  coordinator make_coordinator()
  {
    coordinator coord;
    coord.activate<Ts...>();
    return std::move(coord);
  }

  template<typename... Ts> signature make_signature(coordinator& c)
  {
    signature that;
    (that.set(c.type_of<Ts>()),...);
    return that;
  }
}
