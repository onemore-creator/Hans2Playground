#pragma once
#include "Vec2.hpp"

namespace Halib::Data
{
	struct Camera
	{
		Vec2 position{0};

		/// @brief 
		/// @param zoom Zoom is capped between 0 and 1
		void SetZoom(float zoom);
		float GetZoom();
		
		short GetSpriteScale();
		
		private:
		float zoom = 1.0f;
		short spriteScale = -1;
	};
} // namespace Halib::Data
