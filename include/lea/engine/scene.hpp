//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <lea/api.hpp>
#include <lea/engine/ecs.hpp>
#include <lea/engine/component/display.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <optional>
#include <memory>

namespace sf
{
  class RenderTarget;
  class Event;
}

namespace lea
{
  using transition = std::optional<std::string>;

  struct game;
  struct drawing;

  struct LEA_API scene
  {
    scene();
    virtual ~scene();

    void draw(sf::RenderTarget& target, sf::Transform const& transform = {}) const;
    coordinator& manager() { return coordinator_; }

    virtual transition  process(sf::Event&)         { return {};  }
    virtual transition  update_logic(std::uint32_t) { return {};  }
    virtual void        update_display(double)      {}

    protected:
    coordinator               coordinator_;
    sf::Transform             transform_;
    drawing*                  drawing_system_;
    game*                     parent_;
  };

  using scene_t = std::unique_ptr<scene>;
}
