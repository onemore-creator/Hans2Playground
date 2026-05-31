#pragma once
#include "Camera.hpp"
#include "Entity.hpp"
#include "Image.hpp"
#include "Sprite.hpp"
#include <memory>

extern Camera camera;

void Init();
void FinishFrame();

/// @brief Shows the given image and fades it into dark over the span of 5.8 s
void ShowCoolTitle(std::shared_ptr<Image> image, short x, short y);

/// @brief Renders an image at the given position. Origin is top left
void Render(const std::shared_ptr<Image> image, short x, short y,
            short xScale = 1, short yScale = 1);

/// @brief Renders a sprite at the given position
void Render(const std::shared_ptr<Sprite> sprite, short x, short y);

/// @brief Renders an entity at the given position
void Render(const std::shared_ptr<Entity> entity);

/// @brief Sets the whole screen to the given color
void Clear(Hall::Color color);