#include <Hall/Hall.h>
#include "Time.hpp"
#include "System.hpp"
#include <memory>
#include <iostream>

using namespace Halib;

int main() 
{
	Hall::Init();
	System::Init();
	Time::SetTargetFramerate(30);
	
	while(!Hall::ShouldClose())
	{
		std::cout << Halib::Time::GetDeltaTime() << std::endl;
		System::FinishFrame();
	}
	
	return 0;
}