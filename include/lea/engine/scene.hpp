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
#include <lea/engine/drawable.hpp>
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

  struct LEA_API scene : drawable
  {
    scene();

    void draw(sf::RenderTarget& target, sf::Transform const& transform = {}) const override;

    void insert( drawable_t && d ) { children_.push_back( std::move(d) ); }

    auto begin()  const { return children_.begin(); }
    auto end()    const { return children_.end(); }

    virtual transition  process(sf::Event& e);
    virtual transition  update_logic(std::uint32_t frame_id);
    virtual void        update_display(double absolute_time);

    protected:
    sf::Transform           transform_;
    std::vector<drawable_t> children_;
  };

  using scene_t = std::unique_ptr<scene>;
}
