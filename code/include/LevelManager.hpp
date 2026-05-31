#pragma once
#include "Sprite.hpp"
#include <memory>
#include <vector>

namespace Halib
{
	class LevelManager
	{
		struct BackgroundData
		{
			std::shared_ptr<Sprite> tileset;
			std::vector<std::vector<int>> tilemap;
		};

		const char* backgroundPath = "assets/level/background.txt";
		BackgroundData bgData;

		public:
		void Init();
		void Render();
		
	};
} // namespace Halib
