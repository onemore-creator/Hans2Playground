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

	enum class Mode
	{
		NONE,
		ADD,
		DELETE
	};

	const char *backgroundPath = "assets/level/background.txt";
	std::vector<Button> buildModeEnterCode = {Button::A, Button::L, Button::Y, Button::X};
	BackgroundData bgData;

	bool isLevelBuilding = false;

	//Level editing variables - START
	int selectorAnimCounter = 0;
	std::shared_ptr<Sprite> selector;
	//std::shared_ptr<Sprite> selector;
	//std::shared_ptr<Sprite> selector;
	Vec2 selectorPos{160, Hall::SCREEN_HEIGHT - 160};
	const Vec2 tileSize{32};
	int activeItemIndex = 0;
	Mode mode = Mode::NONE;
	//Level editing variables - END

	void BuildCodeChecker();
public:
	void Init();
	void Update();
	void Render();
	void LateRender();

	void EnableLevelBuilder();
	void DisableLevelBuilder();
	bool GetIsLevelBuilding();
};