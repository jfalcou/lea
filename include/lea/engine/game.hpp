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
#include <lea/system/window.hpp>
#include <lea/tools/random.hpp>
#include <lea/api.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>

namespace lea
{
  struct scene;

  struct LEA_API game
  {
    game(const char* configuration_file);
    bool run();

    void update_server(std::uint32_t frame_id);
    void update_client(double delta);

    random& prng() { return prng_; }

    private:
    interpreter             script_manager_;
    std::filesystem::path   configuration_path_;
    window                  display_;
    random                  prng_;
    scene*                  current_scene_;
    double                  time_delta_;
  };
}
