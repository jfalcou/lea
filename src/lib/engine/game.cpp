//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/game.hpp>
#include <lea/system/directory.hpp>
#include <lea/3rd_party/sol.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <unistd.h>

namespace lea
{
  game::game(const char* configuration_file)
      : configuration_path_(get_config(configuration_file))
      , display_ ( [&]()
                  {
                    script_manager_.run(configuration_path_.c_str());
                    sol::table that = script_manager_["settings"];
                    return that;
                  }()
                )
      , time_delta_(1. / display_.settings().frame_rate )
  {
  }

  bool game::run()
  {
    sf::Event event;
    sf::Clock clock;

    std::uint32_t frame_id = 0;

    while(display_.is_open())
    {
      while(display_.poll(event/*,current_scene_*/))
      {
  //      if(!current_screen_->process(event))
        {
          switch(event.type)
          {
            case sf::Event::Closed: display_.close(); break;
            default: break;
          }
        }
      }

      frame_id++;

      // update_server(frame_id);
      // update_client(time_delta_);

//      display_.clear();
//      current_screen_->render(display_);
      display_.show(/*current_scene_*/);
    }

    return true;
  }
}
