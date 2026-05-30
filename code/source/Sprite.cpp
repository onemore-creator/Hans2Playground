#include "Sprite.hpp"


namespace Halib::Data
{
	Sprite::Sprite(std::shared_ptr<Image> image, std::shared_ptr<Image> image75, Vec2 frameCount)
	{
		this->image = image;
		this->image75 = image75;
		this->frameCount = frameCount;
		activeFrame = Vec2(0);
		scale = 1;

		frameSize = image->size / frameCount;
		imageOffset = Vec2(0);
		renderScale = 1;
		renderImage = image;
		animationLength = image->size.y;
	}

	void Sprite::SetScale(short scale)
	{
		this->scale = scale;
		bool useBig = scale & 1  && scale < 0;
		
		if(scale < -4)
		{
			useBig = true;
			renderScale  = scale + 2;
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
	}

	short Sprite::GetScale()
	{
		return scale;
	}

	void Sprite::IncrementAnimation(short amount)
	{
		activeFrame.x += amount;
		activeFrame.x = activeFrame.x % animationLength;
		imageOffset.x = activeFrame.x * frameSize.x;
	}

	void Sprite::SetAnimation(short animationIndex, short animationLength)
	{
		activeFrame.y = animationIndex;
		imageOffset.y = animationIndex * frameSize.y;
		this->animationLength = animationLength;
	}

} // namespace Halib::Data
