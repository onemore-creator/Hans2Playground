#pragma once

#include "EntityManager.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"
#include <memory>
#include <string>

struct Entity {
  Vec2 position = Vec2(0);
  std::shared_ptr<Sprite> sprite;
  bool isActive = true;
  std::string name;

  template <class T, class... Args>
  static std::shared_ptr<T> Create(Args &&...args) {
    static_assert(std::is_base_of_v<Entity, T>,
                  "Create<T>: T must derive from Entity");
    auto entity_ptr = std::make_shared<T>(std::forward<Args>(args)...);
    EntityManager::Register(entity_ptr);
    return entity_ptr;
  }

  Entity() = default;
  Entity(Vec2 position, std::shared_ptr<Sprite> sprite, std::string name);

  // Is called each game tick
  virtual void Update();
};
