//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
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
      window_.create( sf::VideoMode ( settings_.width,settings_.height)
                    , title
                    , sf::Style::Titlebar | sf::Style::Close
                    );
    }

    window_.setFramerateLimit(settings_.frame_rate);

    auto x  = configuration["position"]["x"].get<int>();
    auto y  = configuration["position"]["y"].get<int>();
    window_.setPosition( sf::Vector2i(x, y) );
  }

  bool window::is_open() const
  {
    return window_.isOpen();
  }

  bool window::poll(sf::Event& e)
  {
    return window_.pollEvent(e);
  }

  void window::show()
  {
    window_.display();
  }

  void window::close()
  {
    window_.close();
  }
}
