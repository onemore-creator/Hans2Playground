#include <Hall/Hall.h>
#include <memory>
#include <iostream>
#include <filesystem>
#include "Time.hpp"
#include "System.hpp"
#include "Data.hpp"
#include "Sprite.hpp"

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
	auto image75 = Data::LoadImage("assets/byterLogo75.bmp");
	auto imageShroom = Data::LoadImage("assets/Mushroom-Run.bmp");
	auto imageShroom75 = Data::LoadImage("assets/Mushroom-Run75.bmp");

	auto sprite = std::make_shared<Data::Sprite>(image, image75, Data::Vec2(1));
	auto spriteShroom = std::make_shared<Data::Sprite>(imageShroom, imageShroom75, Data::Vec2(8, 1));
	
	//System::ShowCoolTitle(image, 140, 60);

	int scale = -1;
	int subscale = 0;
	int add = -1;
	bool up = false;
	bool down = false;
	while(!Hall::ShouldClose())
	{
		subscale++;
		if(subscale >= 10)
		{
			subscale = 0;
			scale += add;
			if(scale >= -1)
				add *= -1;
			else if(scale <= -15)
				add *= -1;
		}

		//TODO: Sprite and animation clash. The framesize and imageOffset need to be both updated when animating or changing the scale

		auto cont = Hall::GetController(0);
		bool newUp = Hall::GetUp(cont);
		bool newDown = Hall::GetDown(cont);
		if(!up && newUp)
			spriteShroom->IncrementAnimation(1);
		if(!down && newDown)
			spriteShroom->IncrementAnimation(-1);
		
		up = newUp;
		down = newDown;
		
		sprite->SetScale(scale);
		spriteShroom->SetScale(scale);
		//RENDER CODE
		System::Clear(Data::CreateColor(3, 3, 3, 1));
		//System::Render(image, 100, 60, scale, scale);
		System::Render(sprite, 20, 60);
		System::Render(spriteShroom, 200, 60);
		//RENDER CODE END

		//std::cout << Halib::Time::GetDeltaTime() << std::endl;
		System::FinishFrame();
	}
	
	return 0;
}