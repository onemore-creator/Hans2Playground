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
		Vec2(Hall::SCREEN_WIDTH - 48, 48), 
		LoadSprite("assets/level/LButton.bmp", Vec2(4, 2)), 
		"L-Button Image");
	pencil = Entity::Create<Entity>(
		Vec2(Hall::SCREEN_WIDTH - 48, 16), 
		LoadSprite("assets/level/Pencil.bmp", Vec2(1, 1)), 
		"Pencil Image");
	
	rButton = Entity::Create<Entity>(
		Vec2(Hall::SCREEN_WIDTH - 16, 48),
		LoadSprite("assets/level/RButton.bmp", Vec2(4, 2)),
		"R-Button Image");
	eraser = Entity::Create<Entity>(
		Vec2(Hall::SCREEN_WIDTH - 16, 16),
		LoadSprite("assets/level/Eraser.bmp", Vec2(1, 1)),
		"Eraser image");

	lButton->sprite->SetAnimation(1, 4);
	lButton->sprite->SetActiveFrame(Vec2(3, 1));
	rButton->sprite->SetAnimation(1, 4);
	rButton->sprite->SetActiveFrame(Vec2(3, 1));
	pencil->sprite->SetScale(-2);
	eraser->sprite->SetScale(-2);
	RenderManager::UnregisterEntity(lButton);
	RenderManager::UnregisterEntity(rButton);
	RenderManager::UnregisterEntity(pencil);
	RenderManager::UnregisterEntity(eraser);
}

void Selector::Animate()
{
	if(lButton->sprite->GetActiveFrame().x < lButton->sprite->GetAnimationLength() - 1)
		lButton->sprite->IncrementAnimation(1);
	if(rButton->sprite->GetActiveFrame().x < rButton->sprite->GetAnimationLength() - 1)
		rButton->sprite->IncrementAnimation(1);
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


	if(InputManager::GetButtonDown(0, Button::L)) 
	{
		if(mode == Mode::DELETE)
		{
			rButton->sprite->SetActiveFrame(Vec2(3, 1));
			eraser->sprite->SetScale(-2);
		}
		
		if(mode == Mode::ADD)
		{
			lButton->sprite->SetAnimation(1, 4);
			pencil->sprite->SetScale(-2);
			mode = Mode::NONE;
		}
		else
		{
			lButton->sprite->SetAnimation(0, 4);
			pencil->sprite->SetScale(-1);
			mode = Mode::ADD;
		}
	}

	if(InputManager::GetButtonDown(0, Button::R)) 
	{
		if(mode == Mode::ADD)
		{
			lButton->sprite->SetActiveFrame(Vec2(3, 1));
			pencil->sprite->SetScale(-2);
		}
		
		if(mode == Mode::DELETE)
		{
			rButton->sprite->SetAnimation(1, 4);
			eraser->sprite->SetScale(-2);
			mode = Mode::NONE;
		}
		else
		{
			rButton->sprite->SetAnimation(0, 4);
			eraser->sprite->SetScale(-1);
			mode = Mode::DELETE;
		}
	}

	Animate();
}

void Selector::SetUIVisibility(bool isVisible)
{
	if(isVisible)
	{
		RenderManager::RegisterEntity(lButton, INT16_MAX);
		RenderManager::RegisterEntity(rButton, INT16_MAX);
		RenderManager::RegisterEntity(pencil, INT16_MAX);
		RenderManager::RegisterEntity(eraser, INT16_MAX);
	}
	else
	{
		RenderManager::UnregisterEntity(lButton);
		RenderManager::UnregisterEntity(rButton);
		RenderManager::UnregisterEntity(pencil);
		RenderManager::UnregisterEntity(eraser);
	}
}