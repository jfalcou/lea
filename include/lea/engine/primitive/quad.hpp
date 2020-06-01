//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <lea/engine/drawable.hpp>
#include <lea/api.hpp>

namespace lea
{
  struct LEA_API quad : drawable, private sf::RectangleShape
  {
    quad();
    quad( sf::Vector2f const& pos);
    quad( sf::Vector2f const& pos, sf::Vector2f const& size);
    quad( sf::Vector2f const& pos, sf::Vector2f const& size, sf::Color const& color);

    template<typename... Args>
    static drawable_t make(Args const&... args)
    {
      return std::make_unique<quad>(args...);
    }

  using RectangleShape::setFillColor;
  using RectangleShape::setOutlineColor;
  using RectangleShape::setOutlineThickness;

    void draw(sf::RenderTarget& target, sf::Transform const& transform) const override;
  };
}
