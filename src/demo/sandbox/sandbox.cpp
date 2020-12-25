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
#include <lea/engine/ecs.hpp>
#include <lea/engine/primitive/quad.hpp>
#include <lea/engine/component/display.hpp>

struct transform  { sf::Vector2f position; };

struct random_box_filler : lea::scene
{
  random_box_filler(lea::game& g) : scene(&g), since_last_time_(0.)
  {
    //coordinator_.activate<transform>();
    // display_system_ = coord.accept<display>();
    // coord.set_signature<display>(lea::make_signature<context,transform>(coord_));
  }

  static lea::scene_t make(lea::game& g) { return std::make_unique<random_box_filler>(g); }

  lea::transition process(sf::Event& event) override
  {
    switch(event.type)
    {
      case sf::Event::Closed: { terminate(); return {}; }
      break;

      case sf::Event::KeyPressed:
      {
        if(event.key.code == sf::Keyboard::Escape)  { terminate(); return {}; }
        if(event.key.code == sf::Keyboard::Space)
        {
          for(auto e : entities)
            coordinator_.destroy(e);
          entities.clear();

          return {};
        }
        return {}; break;
      }

      default: return {}; break;
    }
  }

  lea::transition update_logic(std::uint32_t frame_id) override
  {
    auto fps = settings().frame_rate;

    // Every 1/10th of a second, see if we spawn a new block with 66% chance
    if( (frame_id % fps) && prng().check_success(66.f))
    {
      auto edge = 32 + 32*prng().flip();
      entities.push_back( manager().create
                        ( lea::display( lea::quad::make ( sf::Vector2f( prng().roll(0,640-64)
                                                                      , prng().roll(0,480-64)
                                                                      )
                                                        , sf::Vector2f(edge,edge)
                                                        , sf::Color(255,0,0,255)
                                                        )
                                      )
                                  )
                        );
    }

    return {};
  }

  void update_display(double current_time) override
  {
    // // Every half second, change color of every blocks
    // if( (current_time - since_last_time_) > 0.5 )
    // {
    //   //display_system_->update(current_time);
    //   //for(auto& q : entities_ )
    // //     dynamic_cast<lea::quad*>(q.get())->setFillColor ( sf::Color ( prng.flip()*128+127
    // //                                                                 , prng.flip()*128+127
    // //                                                                 , prng.flip()*128+127
    // //                                                                 , prng.roll(128,255)
    // //                                                                 )
    // //                                                     );
    //   // Update time
    //   since_last_time_ = current_time;
    // }
  }

  private:
  std::vector<lea::entity>  entities;
  double                    since_last_time_;
};

int main()
{
  lea::game g("src/demo/sandbox/res/config.lua");

  g.add_scene( "main", random_box_filler::make(g) );
  g.run("main");
}
