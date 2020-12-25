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

struct position { sf::Vector2f coords; };

struct quad_system : lea::system
{
  quad_system(lea::coordinator* c) : lea::system(c) {}

  void draw(sf::RenderTarget& target, sf::Transform const& trf)
  {
    std::cout<< "Display of " << entities.size() << " quads.\n";
    for (auto const& e : entities)
    {
      manager->component<lea::quad>(e).draw(target, trf);
    }
  }
};

struct display_system : lea::system
{
  display_system(lea::coordinator* c) : lea::system(c) {}

  void update(double current_time, auto& prng)
  {
    // Every half second, change color of every blocks
    if( (current_time - since_last_time_) > 0.1 )
    {
      for (auto const& e : entities)
      {
        auto& q = manager->component<lea::quad>(e);
        auto  p = manager->component<position>(e);

        // Turn grid to gfx position
        p.coords.x *=64;
        p.coords.y *=64;

        // Prepare quad
        q.setPosition(p.coords);
        q.setSize({64,64});
        q.setFillColor( sf::Color(128+127*prng.flip(),128+127*prng.flip(),128+127*prng.flip(),255) );

        // Update time
        since_last_time_ = current_time;
      }
    }
  }

  double since_last_time_{};
};
struct logic_system : lea::system
{
  logic_system(lea::coordinator* c) : lea::system(c) {}

  lea::transition update(std::uint32_t frame_id, auto& particules, auto& prng)
  {
    // Move old particles in a brownian fashion
    for (auto const& e : entities)
    {
      auto& p = manager->component<position>(e);
      p.coords.x = std::max(0.f,std::min(10.f, p.coords.x+prng.roll(-1,1)));
      p.coords.y = std::max(0.f,std::min(6.f, p.coords.y+prng.roll(-1,1)));
    }

    // Check to add new particle
    if( (frame_id % 120) && prng.check_success(10.f) && particules.size() < 100)
    {
      particules.push_back( manager->create ( lea::quad()
                                            , position{{prng.roll(0,10),prng.roll(0,6)}}
                                            )
                          );
    }

    return {};
  }

  double since_last_time_{};
};

struct random_box_filler : lea::scene
{
  random_box_filler(lea::game& g) : scene(&g)
  {
    quad_system_    = manager().accept<quad_system>();
    display_system_ = manager().accept<display_system>();
    logic_system_   = manager().accept<logic_system>();

    manager().activate<lea::quad>();
    manager().activate<position>();

    manager().set_signature<quad_system>(lea::make_signature<lea::quad>(manager()));
    manager().set_signature<display_system>(lea::make_signature<lea::quad,position>(manager()));
    manager().set_signature<logic_system>(lea::make_signature<lea::quad,position>(manager()));
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
          for(auto e : entities)  coordinator_.destroy(e);
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
    return logic_system_->update(frame_id, entities, prng());
  }

  void update_display(double current_time) override
  {
    display_system_->update(current_time, prng());
  }

  void do_draw(sf::RenderTarget& target, sf::Transform const& trf) const override
  {
    quad_system_->draw(target,trf);
  }

  private:
  std::vector<lea::entity>  entities;
  quad_system*              quad_system_;
  display_system*           display_system_;
  logic_system*             logic_system_;
};

int main()
{
  lea::game g("src/demo/sandbox/res/config.lua");

  g.add_scene( "main", random_box_filler::make(g) );
  g.run("main");
}
