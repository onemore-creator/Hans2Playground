#pragma once

#include "CollidableEntity.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

struct Player : CollidableEntity {
  Vec2 size;

  // public exposure
  float fallSpeed =
      0.0f; // current vy (px/s). Positive = falling, negative = climbing
  float pitch =
      0.14f; // nose angle (rad). 0 = level, + = nose down, - = nose up
  bool landed = false;

  Player(Vec2 position, Vec2 size);
  Player(Vec2 position, Vec2 size, std::string name);
  Player(Vec2 position, Vec2 size, std::shared_ptr<Sprite> sprite,
         std::string name);
  Player();

  void Update() override;

private:
  // Physics steps (each owns its tuning constants)

  struct Gravity {
    float g = 240.0f; // px/s²
    void apply(float &vy, float dt) const;
  };

  struct Lift {
    // Redirects the velocity vector toward `pitch` - speed-preserving (lift
    // does no work). Turn rate grows with speed (more airflow = more
    // authority).
    float kTurn = 0.045f; // turn-rate = kTurn * speed * angleDelta
    float turnCap = 5.0f; // max rotation rate (rad/s)
    void apply(float &vx, float &vy, float pitch, float dt) const;
  };

  struct Drag {
    float kD = 0.0008f; // quadratic drag: ds = kD * s² * dt
    void apply(float &vx, float &vy, float dt) const;
  };

  struct Integration {
    void apply(Vec2 &position, float vx, float vy, float dt) const;
  };

  struct PitchControl {
    float pitchRate = 1.7f;  // rad/s while button held
    float pitchMin = -0.52f; // nose-up limit  (~-30°)
    float pitchMax = 0.52f;  // nose-down limit (~+30°)
    void apply(float &pitch, bool up, bool down, float dt) const;
  };

  struct Boundary {
    float marginX = 0.0f;
    float marginTop = 0.0f;
    float marginBottom = 0.0f;
    void apply(Vec2 &position, float &vx, float &vy, float &fallSpeed,
               bool &landed, Vec2 size) const;
  };

  struct Flap {
    float speed = 23.0f; // px/s added along the nose on each flap
    // Redirects velocity to the nose direction and adds `speed`.
    void apply(float &vx, float &vy, float pitch) const;
  };

  // Step instances
  Gravity gravity;
  Lift lift;
  Drag drag;
  Integration integration;
  PitchControl pitchCtrl;
  Boundary boundary;
  Flap flapAction;

  // Launch config
  float launchSpeed = 80.0f; // px/s
  float launchPitch = 0.14f; // rad (~8° nose-down — gentle descending start)

  // State
  Vec2 launchPosition;
  float vx = 0.0f;
  float vy = 0.0f;

  int currentAnimation = 1;

  void launch();
};
