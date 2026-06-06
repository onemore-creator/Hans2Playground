#pragma once

#include "Entity.hpp"
#include "Hall/Video.h"
#include "System.hpp"
#include <memory>
#include <set>
#include <map>

struct RenderManager {

  static void Render();

  /// @brief registers the entity to be rendered. Each entity should only ever be registered once
  /// @param entity 
  /// @param renderLayer higher layers are on top of lower layers
  static void RegisterEntity(std::shared_ptr<Entity> entity, short renderLayer);
  static void UnregisterEntity(std::shared_ptr<Entity> entity);
  static void ChangeRenderLayer(std::shared_ptr<Entity> entity, short renderLayer);
private:
  static std::map<short, std::set<std::shared_ptr<Entity>>> entities;

  static void DrawSprite(std::shared_ptr<Entity> entity);
};
