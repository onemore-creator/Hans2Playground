# pragma once
#include <memory>
#include "Image.hpp"
#include "Simage.hpp"
#include "Sprite.hpp"

namespace Halib::System
{
	void Init();
	void FinishFrame();

	/// @brief Shows the given image and fades it into dark over the span of 5.8 s
	void ShowCoolTitle(std::shared_ptr<Data::Image> image, short x, short y);

	/// @brief Renders an image at the given position. Origin is top left
	void Render(const std::shared_ptr<Data::Image> image, short x, short y, short xScale = 1, short yScale = 1);
	
	/// @brief Renders an simage at the given position with the given scale
	void Render(const std::shared_ptr<Data::Simage> simage, short x, short y, short scale = 1);

	/// @brief Renders a sprite at the given position
	void Render(const std::shared_ptr<Data::Sprite> sprite, short x, short y);

	/// @brief Sets the whole screen to the given color
	void Clear(Hall::Color color);

} // namespace Halib::System
