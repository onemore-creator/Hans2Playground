# pragma once
#include <memory>
#include "Image.hpp"

namespace Halib::System
{
	void Init();
	void FinishFrame();

	/// @brief Renders an image at the given position. Origin is top left
	void Render(const std::shared_ptr<Data::Image> image, short x, short y);

	/// @brief Sets the whole screen to the given color
	void Clear(Hall::Color color);

} // namespace Halib::System
