#pragma once
#include <Hall/Hall.h>
#include "Image.hpp"
#include "Simage.hpp"
#include <memory>
#include <string>

/// @brief Loads a bitmap image from the file system into RAM and returns a pointer to the loaded image. The image in RAM is always of the type R5G5B5A1
/// @param path the path to the file to load
/// @return A pointer to the loaded image data
std::shared_ptr<Image> LoadImage(std::string path);

/// @brief Loads a bitmap image from the file system into RAM, together with a smaller version of the image. The smaller version is assumed to be 75% the size of the original one. The smaller image's path is assumed to be the original image's name + "75", or can be explicitly set
/// @param path The path to the file to load
/// @param path2 The path to the smaller image to load.
/// @return A pointer to the loaded image data
std::shared_ptr<Simage> LoadSimage(std::string path1, std::string path2 = "");

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
