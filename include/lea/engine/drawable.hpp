//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <lea/api.hpp>
#include <memory>

namespace sf
{
  class RenderTarget;
}

namespace lea
{
  struct LEA_API drawable
  {
    virtual ~drawable();
    virtual void draw(sf::RenderTarget& target, sf::Transform const& transform = {}) const =0;
  };

  using drawable_t = std::unique_ptr<drawable>;
}
