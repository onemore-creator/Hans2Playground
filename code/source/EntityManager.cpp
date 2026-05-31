#include "EntityManager.hpp"
#include "Entity.hpp"
#include <cstdio>
#include <memory>

std::set<std::shared_ptr<Entity>> EntityManager::entities;

void EntityManager::Register(std::shared_ptr<Entity> entity) {
  entities.insert(entity);
}

void EntityManager::Update() {
  for (const std::shared_ptr<Entity> e : entities) {
    printf("position of the %s is (x: %d y: %d)\n", e->name.c_str(),
           e->position.x, e->position.y);
    e->Update();
  }
}
