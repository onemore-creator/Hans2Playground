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
		std::cout << argv[0] << std::endl;
		std::filesystem::current_path(std::filesystem::path(argv[0]).parent_path());
	}
#else
int main() 
{
#endif
	Hall::Init();
	System::Init();
	Time::SetTargetFramerate(30);

	auto image = Data::LoadImage("assets/byterLogo.bmp");
	
	while(!Hall::ShouldClose())
	{
		//RENDER CODE
		Hall::SetScale(1, 1);
		Hall::SetFlip(false, false);
		Hall::SetColor(1);
		Hall::SetColorTable(Hall::NONE);
		Hall::SetColorSource(Hall::COLOR);
		Hall::SetShape(Hall::RECTANGLE);
		Hall::SetRectangle(0, 0, Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT);

		Hall::Draw();
		while (Hall::GetIsGPUBusy());

	    bool wdr = image->wasDataRequested;
		Hall::SetImage((Hall::Color*)image->GetData(), image->width, image->height);
		image->wasDataRequested = wdr;
		//This check has to happen after the first call to SetImage for any given image
#ifdef DESKTOP
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
	    Hall::SetScreenPosition(50, 50);
	    Hall::Draw();
		
		//RENDER CODE END

		//std::cout << Halib::Time::GetDeltaTime() << std::endl;
		System::FinishFrame();
	}
	
	return 0;
}