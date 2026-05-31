#pragma once

#include "Entity.hpp"
#include "Vec2.hpp"
struct CollidableEntity : Entity {

  struct bbox {
    Vec2 origin;
    Vec2 size;
  };

  bbox collisionSize;
  int velocity;
};
