#include "System.hpp"
#include <Hall/Hall.h>
#include "Time.hpp"

namespace Halib::System
{
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

	void Render(const std::shared_ptr<Data::Image> image, short x, short y)
	{
		//DESKTOP ONLY:
		//GetData sets wasDataRequested to true, thereby forcing the image data to be sent every render to the GPU.
		//In this case, we can garantuee that we will not change the image data, so it is save to set wasDataRequested
		//to its old state
	    bool wasDataRequested = image->wasDataRequested;
		Hall::Color* data = (Hall::Color*)image->GetData();
		image->wasDataRequested = wasDataRequested;

		//Wait until GPU is available
		while (Hall::GetIsGPUBusy())
		;

		Hall::SetImage(data, image->width, image->height);
#ifdef DESKTOP
		//These checks have to happen after the first call to SetImage for any given image
		if(image->wasDataRequested)
		{
			Hall::UpdateRaylibTexture((Hall::Color*)image->GetData(), image->width, image->height);
		} 
		else if(image->wasDataSet)
		{
			Hall::UpdateRaylibTexture((Hall::Color*)image->GetData(), image->width, image->height);
			image->wasDataSet = false;
			image->wasDataRequested = false;
		}
#endif
		Hall::SetColorTable(Hall::CTType::NONE);
        Hall::SetColorSource(Hall::MEMORY);
	    Hall::SetExcerpt(0,0, image->width, image->height);
	    Hall::SetScale(1, 1);
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

} // namespace Halib::System
