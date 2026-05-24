#include <Hall/Hall.h>
#include <memory>
#include <iostream>
#include <filesystem>
#include "Time.hpp"
#include "System.hpp"
#include "Data.hpp"

using namespace Halib;

#ifdef DESKTOP
int main(int argc, char *argv[])
{
	if(argc >= 1)
	{
		std::filesystem::path exeDir = std::filesystem::path(argv[0]).parent_path();
		if(std::filesystem::exists(exeDir / "assets"))
			std::filesystem::current_path(exeDir);
	}
#else
int main() 
{
#endif
	Hall::Init();
	System::Init();
	Time::SetTargetFramerate(60);

	auto image = Data::LoadImage("assets/byterLogo.bmp");
	auto simage = Data::LoadSimage("assets/byterLogo.bmp");
	
	//System::ShowCoolTitle(image, 140, 60);

	int scale = -1;
	int subscale = 0;
	int add = -1;
	bool up = false;
	bool down = false;
	while(!Hall::ShouldClose())
	{
		subscale++;
		if(subscale >= 5)
		{
			subscale = 0;
			scale += add;
			if(scale >= -1)
				add *= -1;
			else if(scale <= -15)
				add *= -1;
		}

		/*auto cont = Hall::GetController(0);
		bool newUp = Hall::GetUp(cont);
		bool newDown = Hall::GetDown(cont);
		if(!up && newUp)
			scale++;
		if(!down && newDown)
			scale--;
		
		up = newUp;
		down = newDown;*/
		
		//RENDER CODE
		System::Clear(Data::CreateColor(0, 0, 0, 1));
		//System::Render(image, 100, 60, scale, scale);
		System::Render(simage, 160, 60, scale);
		//RENDER CODE END

		//std::cout << Halib::Time::GetDeltaTime() << std::endl;
		System::FinishFrame();
	}
	
	return 0;
}