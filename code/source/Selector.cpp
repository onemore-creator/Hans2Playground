#include "Selector.hpp"
#include "InputManager.hpp"
#include "Data.hpp"
#include "RenderManager.hpp"

Selector::Selector(Vec2 position, std::string name)
{
	this->position = position;
  	this->name = name;
  	this->sprite = LoadSprite("assets/level/selector.bmp", Vec2(2, 1));

	lButton = Entity::Create<Entity>(
		Vec2(Hall::SCREEN_WIDTH - 80, 48), 
		LoadSprite("assets/level/LButton.bmp", Vec2(4, 2)), 
		"L-Button Image");
	pencil = Entity::Create<Entity>(
		Vec2(Hall::SCREEN_WIDTH - 80, 16), 
		LoadSprite("assets/level/Pencil.bmp", Vec2(1, 1)), 
		"Pencil Image");
	//rButton = LoadSprite(???, ??);
	//eraser = LoadSprite(???, Vec2(1, 1));

	lButton->sprite->SetAnimation(1, 4);
	RenderManager::UnregisterEntity(lButton);
	RenderManager::UnregisterEntity(pencil);
}

//This update is not called in the normal update, but in the level editor update
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

void Selector::SetUIVisibility(bool isVisible)
{
	if(isVisible)
	{
		RenderManager::RegisterEntity(lButton, INT16_MAX);
		RenderManager::RegisterEntity(pencil, INT16_MAX);
	}
	else
	{
		RenderManager::UnregisterEntity(lButton);
		RenderManager::UnregisterEntity(pencil);
	}
}