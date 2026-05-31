#include "Data.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Hall/System.h"
#include "InputManager.hpp"
#include "Rect.hpp"
#include "RenderManager.hpp"
#include "Sprite.hpp"
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

  auto image = LoadImage(std::string("assets/byterLogo.bmp"));
  auto image75 = LoadImage(std::string("assets/byterLogo75.bmp"));
  auto imageShroom = LoadImage(std::string("assets/Mushroom-Run.bmp"));
  auto imageShroom75 = LoadImage(std::string("assets/Mushroom-Run75.bmp"));

  auto sprite = std::make_shared<Sprite>(image, image75, Vec2(1));
  auto spriteShroom =
      std::make_shared<Sprite>(imageShroom, imageShroom75, Vec2(8, 1));

  std::shared_ptr<Rect> player =
      Entity::Create<Rect>(Vec2(20, 20), Vec2(14, 14), sprite, "Player 1");
  // std::shared_ptr<Entity> entity =
  //     Entity::Create<Rect>(Vec2(100, 100), Vec2(14, 14), "Player 1");
  // entity->position = Vec2(100, 100);
  // entity->sprite = sprite;
  //
  // auto entityShroom = std::make_shared<Entity>();
  // entityShroom->position = Vec2(260, 100);
  // entityShroom->sprite = spriteShroom;

  // System::ShowCoolTitle(image, 140, 60);

  int scale = -1;
  int subscale = 0;
  int add = -1;
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;

  while (!Hall::ShouldClose()) {

    System::Clear(CreateColor(0, 0, 0, 1));
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
