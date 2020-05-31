//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/game.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

namespace lea
{
  game::game()
  {
    window_.create( sf::VideoMode(640,480)
                  , "This is the basic game window"
                  , sf::Style::Titlebar | sf::Style::Close
                  );

    window_.setPosition( sf::Vector2i(100, 100) );
    window_.setFramerateLimit(120);
  }

  bool game::run()
  {
    sf::Event event;
    sf::Clock clock;

    std::uint32_t frame_id = 0;

    while(window_.isOpen())
    {
      sf::Time time = clock.restart();
      double elapsed = 1e-6 * time.asMicroseconds();
//      accumulated_time_ += elapsed;

      while(window_.pollEvent(event))
      {
  //      if(!current_screen_->process(event))
        {
          switch(event.type)
          {
            case sf::Event::Closed: window_.close(); break;
            default: break;
          }
        }
      }

      frame_id++;

      // update_server(frame_id);
      // update_client(time_delta_);

      window_.clear();
//      current_screen_->render(window_);
      window_.display();
    }

    return true;
  }
}
