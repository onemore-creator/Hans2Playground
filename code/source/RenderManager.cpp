
#include "RenderManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

void RenderManager::Update() {

  auto entities = EntityManager::entities;

  for (const std::shared_ptr<Entity> e : entities) {
    DrawSprite(e);
  }
}
