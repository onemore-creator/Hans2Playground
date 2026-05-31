#pragma once

#include "CollidableEntity.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

struct Rect : CollidableEntity {
  Vec2 size;

  // Public exposure
  float fallSpeed = 0.0f; // current downward velocity (px/s). Positive =
                          // falling, negative = climbing
  float angle = 0.0f; // nose angle in radians. 0 = level, positive = nose down,
                      // negative = nose up

  Rect(Vec2 position, Vec2 size);
  Rect(Vec2 position, Vec2 size, std::string name);
  Rect(Vec2 position, Vec2 size, std::shared_ptr<Sprite> sprite,
       std::string name);
  Rect();

  void Update() override;

private:
  // Tuning
  float dragCoeff = 0.003f; // lumped drag constant (½ρCwA / mass)  (1 / px)
  float weight = 1.0f;      // gravity multiplier
  float gravity = 180.0f;   // downward acceleration                 (px / s²)
  float thrustX = 50.0f;    // thrust along nose axis                (px / s²)
  float rotateSpeed = 2.5f; // nose rotation rate                    (rad / s)
  float angleMin = -1.1f;   // max nose-up  angle (~63°)             (rad)
  float angleMax = 1.1f;    // max nose-down angle (~63°)            (rad)
  float pitchImpulse =
      -150.0f; // instant upward burst on A/B           (px / s)

  // margins
  float marginX = 40.0f, marginTop = 40.0f, marginBottom = 40.0f;

  // State
  Vec2 launchPosition;
  float vx = 0.0f;
  float vy = 0.0f;
  bool landed = false;

  void launch();
};
