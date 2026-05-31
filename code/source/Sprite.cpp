#include "Sprite.hpp"

Sprite::Sprite(std::shared_ptr<Image> image, std::shared_ptr<Image> image75, Vec2 frameCount)
{
	this->image = image;
	this->image75 = image75;
	this->frameCount = frameCount;
	activeFrame = Vec2(0);
	SetScale(-1);

	frameSize = image->size / frameCount;
	imageOffset = Vec2(0);
	renderScale = 1;
	renderImage = image;
	animationLength = image->size.y;
}

void Sprite::SetScale(short scale)
{
	this->scale = scale;
	bool useBig = scale & 1 && scale < 0;

	if (scale < -4)
	{
		useBig = true;
		renderScale = scale + 2;
	}
	else if (scale < 0)
	{
		renderScale = (scale - 1) / 2;
	}
	else
	{
		renderScale = scale;
	}

	renderImage = useBig ? image : image75;
	frameSize = renderImage->size / frameCount;
	if (renderScale != 0)
		scaledFrameSize = frameSize / std::abs(renderScale);
	else
		scaledFrameSize = 0;
	imageOffset = activeFrame * frameSize;
}

void Sprite::SetActiveFrame(Vec2 frame)
{
	activeFrame = frame;
	imageOffset = activeFrame * frameSize;
}

short Sprite::GetScale()
{
	return scale;
}

Vec2 Sprite::GetScaledFrameSize()
{
	return scaledFrameSize;
}

Vec2 Sprite::GetFrameCount()
{
	return frameCount;
}

void Sprite::IncrementAnimation(short amount)
{
	activeFrame.x += amount;
	activeFrame.x = activeFrame.x % animationLength;
	imageOffset.x = activeFrame.x * frameSize.x;
}

void Sprite::SetAnimation(short animationIndex, short animationLength)
{
	activeFrame.x = 0;
	activeFrame.y = animationIndex;
	imageOffset.y = animationIndex * frameSize.y;
	this->animationLength = animationLength;
}