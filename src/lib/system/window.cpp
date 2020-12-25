//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/scene.hpp>
#include <lea/system/window.hpp>

namespace lea
{
  window::window(sol::table const& configuration)
        : settings_ { configuration["resolution"]["width"].get<int>()
                    , configuration["resolution"]["height"].get<int>()
                    , configuration["frame_rate"].get<int>()
                    , configuration["fullscreen"].get<bool>()
                    }
  {
    auto title  = configuration["title"].get<std::string>();

    if(settings_.fullscreen)
    {
      sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
      settings_.width = desktop.width;
      settings_.height = desktop.height;

      window_.create( sf::VideoMode ( settings_.width, settings_.height)
                    , title
                    , sf::Style::Fullscreen
                    );
    }
    else
    {
      window_.create( sf::VideoMode ( settings_.width, settings_.height )
                    , title
                    , sf::Style::Titlebar | sf::Style::Close
                    );
    }

    window_.setFramerateLimit(settings_.frame_rate);

    auto x  = configuration["position"]["x"].get<int>();
    auto y  = configuration["position"]["y"].get<int>();
    window_.setPosition( sf::Vector2i(x, y) );

    // Initialize rendering texture
    target_.create(settings_.width,settings_.height);

    // Initialize canevas
    canevas_.setSize(sf::Vector2f(settings_.width,settings_.height));
    canevas_.setFillColor( sf::Color(255,255,255,255) );
  }

  bool window::is_open() const
  {
    return window_.isOpen();
  }

  bool window::poll(sf::Event& e)
  {
    return window_.pollEvent(e);
  }

  void window::show(scene& s)
  {
    // Clear target texture
    target_.clear( sf::Color(0,255,0,255) );

    // Draw scene
    s.draw(target_);

    // Retrieve texture
    target_.display();
    auto txt = target_.getTexture();

    // Render to main target
    canevas_.setTexture(&txt);
    window_.draw(canevas_);

    window_.display();
  }

  void window::close()
  {
    window_.close();
  }
}
