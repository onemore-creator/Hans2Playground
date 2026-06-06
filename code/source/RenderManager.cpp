
#include "RenderManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include <vector>

std::map<short, std::set<std::shared_ptr<Entity>>> RenderManager::entities{};


void RenderManager::Render() {
  for(auto& pair : entities)
  {
    for(std::shared_ptr<Entity> entity : pair.second)
    {
      DrawSprite(entity);
    }
  }
}

void RenderManager::RegisterEntity(std::shared_ptr<Entity> entity, short renderLayer)
{
  if(!entities.count(renderLayer)) entities[renderLayer] = std::set<std::shared_ptr<Entity>>();

  entities[renderLayer].insert(entity);
}

void RenderManager::UnregisterEntity(std::shared_ptr<Entity> entity)
{
  std::vector<short> emptyLayers{};
  for(auto& pair : entities)
  {
    pair.second.erase(entity);
    if(pair.second.empty())
      emptyLayers.push_back(pair.first);
  }

  for(auto& layer : emptyLayers)
  {
    entities.erase(layer);
  }
}

void RenderManager::ChangeRenderLayer(std::shared_ptr<Entity> entity, short renderLayer)
{
  UnregisterEntity(entity);
  RegisterEntity(entity, renderLayer);
}


void RenderManager::DrawSprite(std::shared_ptr<Entity> entity) 
{
  while (Hall::GetIsGPUBusy()) 
  {
  }

  ::Render(entity);
}