//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <lea/engine/interpreter.hpp>
#include <lea/engine/scene.hpp>
#include <lea/system/window.hpp>
#include <lea/system/random.hpp>
#include <lea/api.hpp>
#include <filesystem>

namespace lea
{
  struct scene;

  struct LEA_API game
  {
    game(const char* configuration_file);
    bool run(std::string const& id);

    void         add_scene(std::string const& id, scene_t&& s) { scenes_[id] = std::move(s); }
    void         close()                                       { display.close();            }
    setup const& settings() const                              { return display.settings();  }

    scene* find_scene(std::string const& id);

    interpreter                             scripts;
    window                                  display;
    random                                  prng;

    private:
    std::unordered_map<std::string,scene_t> scenes_;
  };
}
