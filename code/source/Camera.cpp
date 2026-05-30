#include "Camera.hpp"
#include <cmath>
#include <algorithm>

namespace Halib::Data
{
	void Camera::SetZoom(float zoom)
	{
		zoom = std::clamp(zoom, 0.0f, 1.0f);
		this->zoom = zoom;
		spriteScale = -std::round(1 / zoom);
	}

	float Camera::GetZoom()
	{
		return zoom;
	}

	short Camera::GetSpriteScale()
	{
		return spriteScale;
	}
} // namespace Halib::Data
