#pragma once
#include "Image.hpp"
#include "Vec2.hpp"

namespace Halib::System {
void Render(const std::shared_ptr<Sprite> image, short x, short y);
}

class Sprite {
  friend void Halib::System::Render(const std::shared_ptr<Sprite> image,
                                    short x, short y);

  std::shared_ptr<Image> image;
  std::shared_ptr<Image> image75;
  Vec2 frameCount;
  Vec2 activeFrame;
  short scale;

  Vec2 frameSize;
  Vec2 scaledFrameSize;
  Vec2 imageOffset;
  short renderScale;
  std::shared_ptr<Image> renderImage;

  short animationLength;

public:
  Sprite(std::shared_ptr<Image> image, std::shared_ptr<Image> image75,
         Vec2 frameCount);

  void SetScale(short scale);
  short GetScale();
  Vec2 GetScaledFrameSize();

  void IncrementAnimation(short amount);
  void SetAnimation(short animationIndex, short animationLength);
};
