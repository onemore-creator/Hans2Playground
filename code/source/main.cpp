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
	
	while(!Hall::ShouldClose())
	{
		//RENDER CODE
		System::Clear(1);
		System::Render(image, 50, 50);
		//RENDER CODE END

		std::cout << Halib::Time::GetDeltaTime() << std::endl;
		System::FinishFrame();
	}
	
	return 0;
}