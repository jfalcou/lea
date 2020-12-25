//==================================================================================================
/**
  LEA - Little Engine Adventure
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <lea/engine/scene.hpp>
#include <lea/engine/game.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace lea
{
  scene::scene(game* p) : transform_{}, parent_(p)
  {
    coordinator_.activate<lea::display>();
    drawing_system_ = coordinator_.accept<drawing>();
    coordinator_.set_signature<drawing>(lea::make_signature<lea::display>(coordinator_));
  }

  scene::~scene() {}

  interpreter&    scene::scripts()        { return parent_->scripts;    }
  window&         scene::display()        { return parent_->display;    }
  random&         scene::prng()           { return parent_->prng ;      }
  setup    const& scene::settings() const { return parent_->settings(); }
  void            scene::terminate()      { parent_->close();           }

  void scene::draw(sf::RenderTarget& target, sf::Transform const& transform) const
  {
    // Combine the parent transform with the scene's one
    sf::Transform combo = transform * transform_;
    target.clear( sf::Color(0,0,0,255) );

    // Let the node draw itself
    drawing_system_->draw(target, combo);
  }
}
