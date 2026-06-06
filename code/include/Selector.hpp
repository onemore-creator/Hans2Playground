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
	
	void Update() override;
	short animCounter = 0;
	Mode mode = Mode::NONE;
	
	public:
	Selector(Vec2 position, std::shared_ptr<Sprite> sprite, std::string name = "Selector");
};