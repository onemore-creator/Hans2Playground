#pragma once
#include "Entity.hpp"
#include <memory>
#include <vector>
#include "InputManager.hpp"

class LevelManager
{
	struct BackgroundData
	{
		std::shared_ptr<Sprite> tileset;
		std::vector<std::vector<int>> tilemap;
	};

	const char *backgroundPath = "assets/level/background.txt";
	std::vector<Button> buildModeEnterCode = {Button::A, Button::L, Button::Y, Button::X};
	BackgroundData bgData;

	bool isLevelBuilding = false;

	//Level editing variables - START
	int selectorAnimCounter = 0;
	std::shared_ptr<Entity> selector;
	//std::shared_ptr<Sprite> selector;
	//std::shared_ptr<Sprite> selector;
	const Vec2 tileSize{32};
	int activeItemIndex = 0;
	
	//Level editing variables - END

	void BuildCodeChecker();
public:
	void Init();
	void Update();
	void Render();

	void EnableLevelBuilder();
	void DisableLevelBuilder();
	bool GetIsLevelBuilding();
};