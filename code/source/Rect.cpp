#include "Rect.hpp"
#include "Hall/Video.h"
#include "InputManager.hpp"
#include "Time.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <memory>
#include <string>

Rect::Rect(Vec2 position, Vec2 size) {
  this->launchPosition = position;
  this->size = size;
  this->name = "default";
  launch();
}

Rect::Rect(Vec2 position, Vec2 size, std::string name) {
  this->launchPosition = position;
  this->size = size;
  this->name = name;
  launch();
}

Rect::Rect(Vec2 position, Vec2 size, std::shared_ptr<Sprite> sprite,
           std::string name) {
  this->launchPosition = position;
  this->size = size;
  this->name = name;
  this->sprite = sprite;
  launch();
}
Rect::Rect() {
  this->position = Vec2();
  this->launchPosition = Vec2();
  this->size = Vec2();
  this->name = "";
}

void Rect::launch() {
  this->position = this->launchPosition;
  this->vx = 0.0f;
  this->vy = 0.0f;
  this->angle = 0.0f;
  this->fallSpeed = 0.0f;
  this->landed = false;
}

void Rect::Update() {
  float dt = Halib::Time::GetDeltaTime();

  if (!this->landed) {
    // Nose rotation
    if (InputManager::GetButtonDown(0, Button::Up))
      this->angle -= this->rotateSpeed * dt;
    if (InputManager::GetButtonDown(0, Button::Down))
      this->angle += this->rotateSpeed * dt;

    this->angle =
        std::max(this->angleMin, std::min(this->angleMax, this->angle));

    // Air resistance
    // F_drag = dragCoeff * v²  (opposes the full velocity vector)
    float speed = std::sqrt(this->vx * this->vx + this->vy * this->vy);
    float dragX = this->dragCoeff * speed * this->vx;
    float dragY = this->dragCoeff * speed * this->vy;

    // Forces
    // Thrust is applied along the nose direction
    float forceX = this->thrustX * std::cos(this->angle) - dragX;
    float forceY = this->thrustX * std::sin(this->angle) +
                   this->weight * this->gravity - dragY;

    //  Integrate
    this->vx += forceX * dt;
    this->vy += forceY * dt;

    this->position.x += this->vx * dt;
    this->position.y += this->vy * dt;

    this->fallSpeed = this->vy;

    // Wrap at right edge
    if (this->position.x > Hall::SCREEN_WIDTH - this->size.x - this->marginX)
      this->position.x = this->marginX;

    // Ceiling
    if (this->position.y < this->marginTop) {
      this->position.y = this->marginTop;
      if (this->vy < 0.0f)
        this->vy = 0.0f;
    }

    // Floor land
    float floorY = Hall::SCREEN_HEIGHT - this->size.y - this->marginBottom;
    if (this->position.y >= floorY) {
      this->position.y = floorY;
      this->vx = 0.0f;
      this->vy = 0.0f;
      this->fallSpeed = 0.0f;
      this->landed = true;
    }
  }

  printf("angle: %.2f  vx: %.1f  vy: %.1f\n", this->angle, this->vx, this->vy);

  // A/B: pitch burst in flight, relaunch when landed
  if (InputManager::GetButtonDown(0, Button::A) ||
      InputManager::GetButtonDown(0, Button::B)) {
    if (this->landed)
      launch();
    else
      this->vy += this->pitchImpulse;
  }
}
