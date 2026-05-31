#include "Player.hpp"
#include "Hall/Video.h"
#include "InputManager.hpp"
#include "Time.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <memory>
#include <string>

static constexpr float kPi = 3.14159265358979f;

// ── Constructors ─────────────────────────────────────────────────────────────

Player::Player(Vec2 position, Vec2 size) {
  this->launchPosition = position;
  this->size = size;
  this->name = "default";
  launch();
}

Player::Player(Vec2 position, Vec2 size, std::string name) {
  this->launchPosition = position;
  this->size = size;
  this->name = name;
  launch();
}

Player::Player(Vec2 position, Vec2 size, std::shared_ptr<Sprite> sprite,
               std::string name) {
  this->launchPosition = position;
  this->size = size;
  this->name = name;
  this->sprite = sprite;
  launch();
}

Player::Player() {
  this->position = Vec2();
  this->launchPosition = Vec2();
  this->size = Vec2();
  this->name = "";
}

void Player::launch() {
  position = launchPosition;
  pitch = launchPitch;
  vx = launchSpeed * std::cos(launchPitch);
  vy = launchSpeed * std::sin(launchPitch);
  fallSpeed = 0.0f;
  landed = false;
  sprite->SetAnimation(1, 30);
}

// Physics steps

void Player::Gravity::apply(float &vy, float dt) const { vy += g * dt; }

void Player::Lift::apply(float &vx, float &vy, float pitch, float dt) const {
  float s = std::sqrt(vx * vx + vy * vy);
  if (s < 1e-6f)
    return;

  // current flight-path angle
  float path = std::atan2(vy, vx);

  // angular error: how far the path is from the nose
  float d = pitch - path;
  while (d > kPi)
    d -= 2.0f * kPi;
  while (d < -kPi)
    d += 2.0f * kPi;

  // turn rate grows with speed; capped so fast flight isn't uncontrollable
  float rate = std::max(-turnCap, std::min(turnCap, kTurn * s * d));
  path += rate * dt;

  // rewrite velocity — same magnitude, new direction (lift does no work)
  vx = s * std::cos(path);
  vy = s * std::sin(path);
}

void Player::Drag::apply(float &vx, float &vy, float dt) const {
  float s = std::sqrt(vx * vx + vy * vy);
  if (s < 1e-6f)
    return;
  float s2 = std::max(0.0f, s - kD * s * s * dt);
  vx *= s2 / s;
  vy *= s2 / s;
}

void Player::Integration::apply(Vec2 &position, float vx, float vy,
                                float dt) const {
  position.x += vx * dt;
  position.y += vy * dt; // screen-space: +y is down
}

void Player::PitchControl::apply(float &pitch, bool up, bool down,
                                 float dt) const {
  if (up)
    pitch = std::max(pitchMin, pitch - pitchRate * dt);
  if (down)
    pitch = std::min(pitchMax, pitch + pitchRate * dt);
}

void Player::Boundary::apply(Vec2 &position, float &vx, float &vy,
                             float &fallSpeed, bool &landed, Vec2 size) const {
  // Ceiling
  if (position.y < marginTop) {
    position.y = marginTop;
    if (vy < 0.0f)
      vy = 0.0f;
  }

  // Floor → land
  float floorY = Hall::SCREEN_HEIGHT - size.y - marginBottom;
  if (position.y >= floorY) {
    position.y = floorY;
    vx = 0.0f;
    vy = 0.0f;
    fallSpeed = 0.0f;
    landed = true;
  }

  // Right-edge wrap
  if (position.x > Hall::SCREEN_WIDTH - size.x - marginX)
    position.x = marginX;
}

void Player::Flap::apply(float &vx, float &vy, float pitch) const {
  float s = std::sqrt(vx * vx + vy * vy);
  float ns = s + speed;
  // redirect to nose direction and inject energy
  vx = ns * std::cos(pitch);
  vy = ns * std::sin(pitch);
}

// Update

void Player::Update() {
  float dt = GetDeltaTime();

  if (!landed) {
    pitchCtrl.apply(pitch, InputManager::GetButton(0, Button::Up),
                    InputManager::GetButton(0, Button::Down), dt);

    gravity.apply(vy, dt);
    lift.apply(vx, vy, pitch, dt);
    drag.apply(vx, vy, dt);
    integration.apply(position, vx, vy, dt);

    fallSpeed = vy;

    boundary.apply(position, vx, vy, fallSpeed, landed, size);
  }

  float speed = std::sqrt(vx * vx + vy * vy);
  float path = std::atan2(vy, vx);
  printf("pitch:%.2f  path:%.2f  spd:%.1f  vx:%.1f  vy:%.1f  landed:%d\n",
         pitch, path, speed, vx, vy, (int)landed);

  // A/B: flap in flight, relaunch when landed
  if (InputManager::GetButtonDown(0, Button::A) ||
      InputManager::GetButtonDown(0, Button::B)) {
    if (landed)
      launch();
    else
      flapAction.apply(vx, vy, pitch);
  }

  if (pitch > 0.1 && currentAnimation != 2) {
    sprite->SetAnimation(2, 30);
    currentAnimation = 2;
  }
  if (pitch < -0.1 && currentAnimation != 3) {
    sprite->SetAnimation(3, 30);
    currentAnimation = 3;
  }
  if (pitch < 0.1 && pitch > -0.1 && currentAnimation != 1) {
    sprite->SetAnimation(1, 30);
    currentAnimation = 1;
  }
  sprite->IncrementAnimation(1);
}
