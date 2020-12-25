//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/game.hpp>
#include <lea/engine/scene.hpp>
#include <lea/system/directory.hpp>
#include <lea/3rd_party/sol.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

namespace lea
{
  game::game(const char* configuration_file)
      : scripts(get_config(configuration_file).c_str())
      , display([&](){ sol::table that = scripts["settings"]; return that; }() )
      , prng(scripts)
  {}

  scene* game::find_scene(std::string const& id)
  {
    auto n = scenes_.find(id);
    if(n == scenes_.end())  return nullptr;
    else                    return n->second.get();
  }

  bool game::run(std::string const& id)
  {
    sf::Clock     clock;
    sf::Event     event;
    double        absolute_time_  = 0.;
    std::uint32_t frame_id        = 0;
    transition    next            = {};

    // Checks we can play the requested scene
    auto* current_scene = find_scene(id);

    // As long as we're running the window
    while(display.is_open() && current_scene)
    {
      sf::Time time   = clock.restart();
      double elapsed  = 1e-6 * time.asMicroseconds();
      absolute_time_ += elapsed;

      // Process event in current scene
      while(display.poll(event))
      {
        next = current_scene->process(event);
      }

      if( display.is_open() )
      {
        if( !next )
        {
          // If no transition has been triggered by events, process next frame
          frame_id++;

          next = current_scene->update_logic(frame_id);
          current_scene->update_display(absolute_time_);
          display.show( *current_scene );
        }

        // If transition has been triggered by scene logic, change the scene
        if( next ) current_scene = find_scene(*next);
      }
    }

    return true;
  }
}
