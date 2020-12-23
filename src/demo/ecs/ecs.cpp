//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/ecs.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <random>

struct gravity    { sf::Vector2f force;     };
struct rigid_body { sf::Vector2f velocity;  };
struct transform  { sf::Vector2f position;  };

struct physics : lea::system
{
  physics( lea::coordinator* cc ) : coord_(cc) {}

  void update(float dt)
  {
    for (auto const& e : entities)
    {
      auto [t,r,g] = coord_->component<transform,rigid_body,gravity>(e);

      t.position.x += r.velocity.x * dt;
      t.position.y += r.velocity.y * dt;
      r.velocity.x += g.force.x * dt;
      r.velocity.y += g.force.y * dt;
    }
  }

  lea::coordinator*  coord_;
};

struct display : lea::system
{
  display( lea::coordinator* cc ) : coord_(cc) {}

  void update(float dt)
  {
    for (auto const& e : entities)
    {
      auto [t,r] = coord_->component<transform,rigid_body>(e);
      std::cout << "[" << &e << "] @ {"
                << t.position.x << ", " << t.position.y << "} @("
                << r.velocity.x << ", " << r.velocity.y << ")\n";
    }
  }

  lea::coordinator*  coord_;
};

int main()
{
  auto coord = lea::make_coordinator<gravity,rigid_body,transform>();

  auto[physics_system, display_system]  = coord.accept<physics, display>();

  coord.set_signature<physics>(lea::make_signature<gravity,rigid_body,transform>(coord));
  coord.set_signature<display>(lea::make_signature<transform,rigid_body>(coord));

  std::vector<lea::entity> entities(10);

  std::default_random_engine generator;
  std::uniform_real_distribution<float> posg( 10.0f, 100.0f);

  for (auto& e : entities)
  {
    e = coord.create( gravity{sf::Vector2f(0.0f, -9.81f)}
                    , rigid_body{ .velocity = sf::Vector2f(0.0f, 0.0f), }
                    , transform{sf::Vector2f(posg(generator), posg(generator))}
                    );
  }

  float dt = 0.01f;

  for(int i=0;i<100;++i)
  {
    std::cout << "Step[" << i <<"]\n";
    physics_system->update(dt);
    display_system->update(dt);
  }
}
