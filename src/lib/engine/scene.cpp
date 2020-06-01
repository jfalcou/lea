//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/scene.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace lea
{
  scene::scene() : transform_{}, children_{} {}

  transition scene::process(sf::Event& )
  {
    return {};
  }

  transition  scene::update_logic(std::uint32_t) { return {};  }
  void        scene::update_display(double)      {}

  void scene::draw(sf::RenderTarget& target, sf::Transform const& transform) const
  {
    // Combine the parent transform with the scene's one
    sf::Transform combo = transform * transform_;
    target.clear( sf::Color(0,0,0,255) );

    // Let the node draw itself
    for(auto& child : children_)
      child->draw(target, combo);
  }
}
