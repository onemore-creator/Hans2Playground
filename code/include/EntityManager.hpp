#pragma once

#include <memory>
#include <set>

struct Entity;

struct EntityManager {

  static std::set<std::shared_ptr<Entity>> entities;

  static void Register(std::shared_ptr<Entity>);
  static void Update();
};
