#pragma once
#include "Entity.hpp"

class Selector : public Entity
{
	enum class Mode
	{
		NONE,
		ADD,
		DELETE
	};
	
	short animCounter = 0;
	Mode mode = Mode::NONE;
	std::shared_ptr<Entity> lButton;
	std::shared_ptr<Entity> rButton;
	std::shared_ptr<Entity> eraser;
	std::shared_ptr<Entity> pencil;
	
	public:
	void Update() override;
	Selector(Vec2 position, std::string name = "Selector");
	void SetUIVisibility(bool isVisible);
};