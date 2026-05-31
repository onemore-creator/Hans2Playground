#pragma once
#include "Image.hpp"

/// @brief A scalable image. Uses two Images to smoothly scale down and up. The second image is 75% the size of the original one
struct Simage
{
	std::shared_ptr<Image> image;
	std::shared_ptr<Image> image75;
};
