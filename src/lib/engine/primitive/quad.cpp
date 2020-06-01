//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/primitive/quad.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

namespace lea
{
  quad::quad() : quad(sf::Vector2f(0.f,0.f))
  {
  }

  quad::quad( sf::Vector2f const& pos)
      : quad(pos, sf::Vector2f(0.f,0.f))
  {
  }

  quad::quad( sf::Vector2f const& pos, sf::Vector2f const& size)
      : quad(pos, size, sf::Color (0,0,0,255))
  {
  }

  quad::quad( sf::Vector2f const& pos, sf::Vector2f const& size, sf::Color const& color)
      : sf::RectangleShape(size)
  {
    sf::RectangleShape::setFillColor(color);
    sf::RectangleShape::setPosition(pos);
  }

  void quad::draw(sf::RenderTarget& target, sf::Transform const& transform) const
  {
    target.draw( static_cast<sf::RectangleShape const&>(*this), transform);
  }
}
