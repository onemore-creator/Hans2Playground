#pragma once

#include "Entity.hpp"
#include "Hall/Video.h"
#include "Rect.hpp"
#include "System.hpp"
#include <memory>
struct RenderManager {

  static void Update();

private:
  static void DrawSprite(std::shared_ptr<Entity> entity) {
    while (Hall::GetIsGPUBusy()) {
    }
    if (auto rect = std::dynamic_pointer_cast<Rect>(entity)) {

      Halib::System::Render(entity);
      Hall::SetRectangle(rect->position.x, rect->position.y, rect->size.x,
                         rect->size.y);
      Hall::SetColorSource(Hall::COLOR);
      Hall::SetColor(Hall::Color(0b1111111111111111));
      Hall::Draw();
    }
  }
};
