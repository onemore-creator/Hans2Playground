#include "Entity.hpp"

Entity::Entity(Vec2 position, std::shared_ptr<Sprite> sprite, std::string name)
{
	this->position = position;
	this->sprite = sprite;
	this->name = name;
}

void Entity::Update()
{
	
}