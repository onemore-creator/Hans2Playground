#pragma once
#include "Sprite.hpp"
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

	void BuildCodeChecker();
public:
	void Init();
	void Update();
	void Render();

	void EnableLevelBuilder();
	void DisableLevelBuilder();
	bool GetIsLevelBuilding();
};