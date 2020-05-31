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
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace lea
{
  struct scene;

  struct LEA_API game
  {
    game();
    bool run();

    private:
    sf::RenderWindow        window_;
    scene*                  current_scene_;
  };
}
