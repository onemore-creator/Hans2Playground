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
} // namespace Halib::System
