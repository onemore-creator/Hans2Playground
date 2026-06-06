#include "Selector.hpp"
#include "InputManager.hpp"

Selector::Selector(Vec2 position, std::shared_ptr<Sprite> sprite, std::string name)
{
	this->position = position;
  	this->name = name;
  	this->sprite = sprite;
}

void Selector::Update()
{
	Vec2 selectorDelta{0};
	if(InputManager::GetButtonDown(0, Button::Right)) selectorDelta.x++;
	if(InputManager::GetButtonDown(0, Button::Left)) selectorDelta.x--;
	if(InputManager::GetButtonDown(0, Button::Down)) selectorDelta.y++;
	if(InputManager::GetButtonDown(0, Button::Up)) selectorDelta.y--;
	
	//32 is the tilesize for the background
	selectorDelta *= 32;
	position += selectorDelta;

	animCounter++;
	if(animCounter >= 30)
	{
		sprite->IncrementAnimation(1);
		animCounter = 0;
	}

	if(InputManager::GetButtonDown(0, Button::L)) mode = mode == Mode::ADD ? Mode::NONE : Mode::ADD;
	if(InputManager::GetButtonDown(0, Button::R)) mode = mode == Mode::DELETE ? Mode::NONE : Mode::DELETE;
}