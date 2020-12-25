//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <lea/engine/drawable.hpp>
#include <lea/engine/ecs.hpp>
#include <iostream>

namespace lea
{
  // Contains the drawable usable by the entity
  struct display { drawable_t  media; };

  struct drawing : system
  {
    drawing( lea::coordinator* cc ) : coord_(cc) {}

    void draw(sf::RenderTarget& target, sf::Transform const& trf)
    {
      std::cout<< "Display of " << entities.size() << " entities.\n";
      for (auto const& e : entities)
      {
        auto& d = coord_->component<display>(e);
        d.media->draw(target, trf);
      }
    }

    coordinator*  coord_;
  };
}
