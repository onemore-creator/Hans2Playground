
#include "RenderManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

int RenderManager::currentAnimation = 1;

void RenderManager::Update() {
  auto entities = EntityManager::entities;
  for (const std::shared_ptr<Entity> e : entities) {
    DrawSprite(e);
  }
}
