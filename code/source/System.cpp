#include "System.hpp"
#include <Hall/Hall.h>
#include "Time.hpp"
#include "Data.hpp"
#include <iostream>

namespace Halib::System
{

	Camera camera{};
	static float time1;

	void Init()
	{
		Time::Init();

		time1 = Time::GetTimeSinceStartup();
	}

	void FinishFrame()
	{
		//In case the GPU is still rendering something, wait until it finished
		while(Hall::GetIsGPUBusy());

		//Wait until VSync is happening
		bool isVsync = Hall::GetVSync();
		bool newIsVsync = Hall::GetVSync();
		while(!(!isVsync && newIsVsync))
		{
			isVsync = newIsVsync;
			newIsVsync = Hall::GetVSync();
		}

		//Swap the frame buffers
		Hall::SetCommandSwapBuffers();

		//Wait until the target frame time has been reached. target frame time = 1 / framerate
		float time2 = Time::GetTimeSinceStartup();
		while (time2 - time1 < Time::GetTargetTimePerFrame()) { time2 = Time::GetTimeSinceStartup(); }

		Time::SetDeltaTime(time2 - time1);
		time1 = time2;
	}

	void ShowCoolTitle(std::shared_ptr<Image> image, short x, short y)
	{
		std::unique_ptr<Hall::Color[]> data = std::make_unique<Hall::Color[]>(image->size.x * image->size.y);
		for(int i = 0; i < image->size.x * image->size.y; i++)
			data.get()[i] = image->GetData()[i];

		std::shared_ptr<Image> titleScreen = std::make_shared<Image>();
		titleScreen->size.x = image->size.x;
		titleScreen->size.y = image->size.y;
		titleScreen->SetData(std::move(data));

		std::cout << "CoolTitle started" << std::endl;
		float timer = 3.0f;
		float time = 0.7f;
		int counter = 0;

		while(!Hall::ShouldClose() && counter < 5)
		{
			timer -= Time::GetDeltaTime();

			if(timer <= 0)
			{
				//Darken each pixel
				Hall::Color* color = titleScreen->GetData();
				for (; color < (titleScreen->GetData() + titleScreen->size.x * titleScreen->size.y); color++)
				{
					*color = SetRed(*color, GetRed(*color) / 2);
					*color = SetGreen(*color, GetGreen(*color) / 2);
					*color = SetBlue(*color, GetBlue(*color) / 2);
				}

				timer = time;
				counter++;
			}

			//RENDER CODE
			System::Clear(1);
			System::Render(titleScreen, x, y);
			//RENDER CODE END
			System::FinishFrame();
		}

		std::cout << "CoolTitle finished" << std::endl;
	}

	void Render(const std::shared_ptr<Image> image, short x, short y, short xScale, short yScale)
	{
		bool wasDataRequested = image->wasDataRequested;
		Hall::Color* data = (Hall::Color*)image->GetData();
		image->wasDataRequested = wasDataRequested;

		while (Hall::GetIsGPUBusy())
		;

		Hall::SetImage(data, image->size.x, image->size.y);
#ifdef DESKTOP
		if(image->wasDataRequested)
		{
			Hall::UpdateRaylibTexture((Hall::Color*)image->GetData(), image->size.x, image->size.y);
		}
		else if(image->wasDataSet)
		{
			Hall::UpdateRaylibTexture((Hall::Color*)image->GetData(), image->size.x, image->size.y);
			image->wasDataSet = false;
			image->wasDataRequested = false;
		}
#endif
		Hall::SetColorTable(Hall::CTType::NONE);
		Hall::SetColorSource(Hall::MEMORY);
		Hall::SetExcerpt(0, 0, image->size.x, image->size.y);
		Hall::SetScale(xScale, yScale);
		Hall::SetFlip(false, false);
		Hall::SetScreenPosition(x, y);
		Hall::Draw();
	}

	void Render(const std::shared_ptr<Simage> simage, short x, short y, short scale)
	{
		if(scale == 0) return;

		short oldScale = scale;
		bool useBig = scale & 1;

		if(scale < -4)
		{
			useBig = true;
			scale  = scale + 2;
		}
		else if (scale < 0)
			scale = (scale - 1) / 2;
		else
			scale = (scale / 2) + 1;

		if(useBig)
			Render(simage->image, x, y, scale, scale);
		else
			Render(simage->image75, x, y, scale, scale);
	}

	void Render(const std::shared_ptr<Sprite> sprite, short x, short y)
	{
		auto image = sprite->renderImage;

		bool wasDataRequested = image->wasDataRequested;
		Hall::Color* data = (Hall::Color*)image->GetData();
		image->wasDataRequested = wasDataRequested;

		while (Hall::GetIsGPUBusy())
		;

		Hall::SetImage(data, image->size.x, image->size.y);
#ifdef DESKTOP
		if(image->wasDataRequested)
		{
			Hall::UpdateRaylibTexture((Hall::Color*)image->GetData(), image->size.x, image->size.y);
		}
		else if(image->wasDataSet)
		{
			Hall::UpdateRaylibTexture((Hall::Color*)image->GetData(), image->size.x, image->size.y);
			image->wasDataSet = false;
			image->wasDataRequested = false;
		}
#endif
		Hall::SetColorTable(Hall::CTType::NONE);
		Hall::SetColorSource(Hall::MEMORY);
		Hall::SetExcerpt(sprite->imageOffset.x, sprite->imageOffset.y, sprite->frameSize.x, sprite->frameSize.y);
		Hall::SetScale(sprite->renderScale, sprite->renderScale);
		Hall::SetFlip(false, false);
		Hall::SetScreenPosition(x, y);
		Hall::Draw();
	}

	void Clear(Hall::Color color)
	{
		while (Hall::GetIsGPUBusy())
		;

		Hall::SetScale(1, 1);
		Hall::SetFlip(false, false);
		Hall::SetColor(color);
		Hall::SetColorTable(Hall::NONE);
		Hall::SetColorSource(Hall::COLOR);
		Hall::SetShape(Hall::RECTANGLE);
		Hall::SetRectangle(0, 0, Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT);

		Hall::Draw();
	}

	void Render(const std::shared_ptr<Entity> entity)
	{
		entity->sprite->SetScale(camera.GetSpriteScale());

		Vec2 position = entity->position;
		position -= Vec2(Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT) / 2;
		position = Vec2((float)position.x * camera.GetZoom(), (float)position.y * camera.GetZoom());
		position += Vec2(Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT) / 2;
		position -= camera.position;
		position -= entity->sprite->GetScaledFrameSize() / 2;

		Render(entity->sprite, position.x, position.y);
	}

} // namespace Halib::System
