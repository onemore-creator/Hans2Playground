#pragma once
#include <Hall/Hall.h>
#include "Image.hpp"
#include <memory>

namespace Halib::Data
{
	/// @brief Loads a bitmap image from the file system into RAM and returns a pointer to the loaded image. The image in RAM is always of the type R5G5B5A1
	/// @param path the path to the file to load
	/// @return A pointer to the loaded image data
	std::shared_ptr<Image> LoadImage(const char* path);


	/// @brief Creates a color from the given values
	/// @param red Must be in range [0, 31]
	/// @param green Must be in range [0, 31]
	/// @param blue Must be in range [0, 31]
	/// @param alpha If true, the pixel is visible, if false, the pixel is transparent
	Hall::Color CreateColor(char red, char green, char blue, bool alpha);

	/// @param red Must be in range [0, 31]
	Hall::Color SetRed(Hall::Color color, char red);

	/// @param green Must be in range [0, 31]
	Hall::Color SetGreen(Hall::Color color, char green);

	/// @param blue Must be in range [0, 31]
	Hall::Color SetBlue(Hall::Color color, char blue);

	/// @param alpha If true, the pixel is visible, if false, the pixel is transparent
	Hall::Color SetAlpha(Hall::Color color, bool alpha);
	
	/// @return The red value in range [0, 31]
	char GetRed(Hall::Color color);

	/// @return The green value in range [0, 31]
	char GetGreen(Hall::Color color);

	/// @return The blue value in range [0, 31]
	char GetBlue(Hall::Color color);

	/// @return The alpha value as bool. If false, the pixel is transparent
	bool GetAlpha(Hall::Color color);

} // namespace Halib::Data
