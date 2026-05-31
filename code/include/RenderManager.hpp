#pragma once

#include "Entity.hpp"
#include "Hall/Video.h"
#include "System.hpp"
#include <memory>

struct RenderManager {

  static void Update();

private:
  static void DrawSprite(std::shared_ptr<Entity> entity) {
    while (Hall::GetIsGPUBusy()) {
    }
    Render(entity);
  }
};
