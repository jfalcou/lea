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
#include <lea/engine/primitive/quad.hpp>

struct random_box_filler : lea::scene
{
  random_box_filler(lea::game& g) : parent_(&g), since_last_time_(0.) {}

  static lea::scene_t make(lea::game& g)
  {
    return std::make_unique<random_box_filler>(g);
  }

  lea::transition process(sf::Event& event) override
  {
    switch(event.type)
    {
      case sf::Event::Closed:
      {
        parent_->close(); return {};
      }
      break;

      case sf::Event::KeyPressed:
      {
        // Pressing [ESC] stops the game
        if(event.key.code == sf::Keyboard::Escape)
        {
          parent_->close();
          return {};
        }

        // Pressing [SPACE] clears the blocks
        if(event.key.code == sf::Keyboard::Space)
        {
          scene::children_.clear();
          return {};
        }

        return {}; break;
      }

      default: return {}; break;
    }
  }

  lea::transition update_logic(std::uint32_t frame_id) override
  {
    auto& prng = parent_->prng();
    auto fps = parent_->settings().frame_rate / 10;

    // Every 1/10th of a second, see if we spawn a new block with 66% chance
    if( (frame_id % fps) == 0 && prng.roll(0,100) <= 66 )
    {
      auto e = 32 + 32*prng.flip();
      scene::insert ( lea::quad::make( sf::Vector2f(prng.roll(0,640-64), prng.roll(0,480-64))
                                     , sf::Vector2f(e,e)
                                     , sf::Color(0,0,0,0)
                                     )
                    );
    }

    return {};
  }

  void update_display(double current_time) override
  {
    auto& prng = parent_->prng();

    // Every half second, change color of every blocks
    if( (current_time - since_last_time_) > 0.5 )
    {
      for(auto& q : scene::children_)
        dynamic_cast<lea::quad*>(q.get())->setFillColor ( sf::Color ( prng.flip()*128+127
                                                                    , prng.flip()*128+127
                                                                    , prng.flip()*128+127
                                                                    , prng.roll(128,255)
                                                                    )
                                                        );
      // Update time
      since_last_time_ = current_time;
    }
  }

  private:
  lea::game*  parent_;
  double      since_last_time_;
};

int main()
{
  lea::game g("src/demo/sandbox/res/config.lua");

  g.add_scene( "main", random_box_filler::make(g) );
  g.run("main");
}
