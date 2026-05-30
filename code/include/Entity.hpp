#pragma once
#include "Vec2.hpp"
#include "Sprite.hpp"
#include <memory>

namespace Halib::Data
{
	struct Entity
	{
		/// @brief Center of the entity. The sprite is pivoted in the center
		Vec2 position;
		std::shared_ptr<Sprite> sprite;
	};
} // namespace Halib::Data
