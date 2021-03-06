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
#include <lea/3rd_party/sol.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

namespace lea
{
  struct scene;

  struct setup
  {
    int width, height;
    int frame_rate;
    bool fullscreen;
  };

  struct LEA_API window
  {
    window(sol::table const& config);

    bool is_open() const;
    bool poll(sf::Event&);
    void show(scene&);
    void close();

    setup const& settings() const { return settings_; }

    private:
    sf::RenderWindow    window_;
    sf::RenderTexture   target_;
    sf::RectangleShape  canevas_;
    setup               settings_;

  };
}
