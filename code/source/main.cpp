#include "Data.hpp"
#include "EntityManager.hpp"
#include "Hall/System.h"
#include "Hall/Video.h"
#include "InputManager.hpp"
#include "Rect.hpp"
#include "RenderManager.hpp"
#include "System.hpp"
#include "Time.hpp"
#include "Vec2.hpp"
#include <Hall/Hall.h>
#include <cstdio>
#include <iostream>
#include <memory>

using namespace Halib;

#ifdef DESKTOP
#include <filesystem>
int main(int argc, char *argv[]) {
  if (argc >= 1) {
    std::filesystem::path exeDir = std::filesystem::path(argv[0]).parent_path();
    if (std::filesystem::exists(exeDir / "assets"))
      std::filesystem::current_path(exeDir);
  }
#else

int main() {
#endif
  Hall::Init();
  System::Init();
  Time::SetTargetFramerate(60);

  EntityManager entityManager;
  RenderManager renderManager;
  InputManager inputManager;

  // points are the top left corner and then width + height
  std::shared_ptr<Rect> player =
      Entity::Create<Rect>(Vec2(20, 20), Vec2(14, 14), "Player 1");

  while (!Hall::ShouldClose()) {

    System::Clear(Data::CreateColor(0, 0, 0, 1));
    // RENDER CODE
    inputManager.Update();
    entityManager.Update();
    renderManager.Update();
    // RENDER CODE END

    std::cout << Halib::Time::GetDeltaTime() << std::endl;
    System::FinishFrame();
  }

  return 0;
}
