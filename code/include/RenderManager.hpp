#pragma once

#include "Entity.hpp"
#include "Hall/Video.h"
#include "Player.hpp"
#include "System.hpp"
#include <algorithm>
#include <memory>

struct RenderManager {

  static void Update();

private:
  static int currentAnimation;
  static void DrawSprite(std::shared_ptr<Entity> entity) {
    while (Hall::GetIsGPUBusy()) {
    }
    if (auto player = std::dynamic_pointer_cast<Player>(entity)) {

      // Default zoom 0.65 (scale -2 / image75). Zooms toward 1.0 as fallSpeed
      // rises 35 → 70. Crossing 0.667 flips GetSpriteScale: -2 → -1 (full img).
      float speed = player->landed ? 35.0f : player->fallSpeed;
      float targetZoom =
          std::clamp((speed - 35.0f) / 35.0f * 0.35f + 0.65f, 0.65f, 1.0f);

      const float maxDelta = 0.008f;
      // gameCamera.SetZoom(
      //     gameCamera.GetZoom() +
      //     std::clamp(targetZoom - gameCamera.GetZoom(), -maxDelta,
      //     maxDelta));

      Render(entity);

      if (player->pitch > 0.1 && currentAnimation != 2) {
        player->sprite->SetAnimation(2, 30);
        currentAnimation = 2;
      }
      if (player->pitch < -0.1 && currentAnimation != 3) {
        player->sprite->SetAnimation(3, 30);
        currentAnimation = 3;
      }
      if (player->pitch < 0.1 && player->pitch > -0.1 &&
          currentAnimation != 1) {
        player->sprite->SetAnimation(1, 30);
        currentAnimation = 1;
      }

      // TODO: consider if it should happen inside the Render(entity)
      entity->sprite->IncrementAnimation(1);

      // Hall::SetRectangle(rect->position.x, rect->position.y, rect->size.x,
      //                    rect->size.y);
      // Hall::SetColorSource(Hall::COLOR);
      // Hall::SetColor(Hall::Color(0b1111111111111111));
      // Hall::Draw();
    }
  }
};
