#include <Hall/Hall.h>
#include <memory>
#include <iostream>
#include "Time.hpp"
#include "System.hpp"
#include "Data.hpp"

using namespace Halib;

int main() 
{
	Hall::Init();
	System::Init();
	Time::SetTargetFramerate(30);

	auto image = Data::LoadImage("assets/byterLogo.bmp");
	
	while(!Hall::ShouldClose())
	{
		//RENDER CODE
		while(Hall::GetIsGPUBusy());
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

		std::cout << Halib::Time::GetDeltaTime() << std::endl;
		System::FinishFrame();
	}
	
	return 0;
}