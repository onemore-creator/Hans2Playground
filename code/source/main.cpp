#include "Data.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Hall/System.h"
#include "Image.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include "RenderManager.hpp"
#include "Sprite.hpp"
#include "System.hpp"
#include "Time.hpp"
#include "Vec2.hpp"
#include "LevelManager.hpp"
#include <Hall/Hall.h>
#include <cstdio>
#include <iostream>
#include <memory>

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
  Init();
  SetTargetFramerate(60);

  EntityManager entityManager;
  RenderManager renderManager;
  InputManager inputManager;
  LevelManager levelManager;

  // points are the top left corner and then width + height

  // Bird flu? yeah they tend to
  auto birdImage = LoadImage(std::string("assets/bird.bmp"));
  auto birdImage75 = LoadImage(std::string("assets/bird75.bmp"));
  // Bird no flu anymore

  auto background = LoadImage(std::string("assets/background.bmp"));

  auto sprite = std::make_shared<Sprite>(birdImage, birdImage75, Vec2(30, 4));

  std::shared_ptr<Player> player =
      Entity::Create<Player>(Vec2(20, 20), Vec2(14, 14), sprite, "Player 1");

  levelManager.Init();
  while (!Hall::ShouldClose()) {
    Render(background, 0, 0);
    inputManager.Update();
    
    if(!levelManager.GetIsLevelBuilding())
      entityManager.Update();
    levelManager.Update();
    
    // RENDER CODE
    levelManager.Render();
    renderManager.Update();
    levelManager.LateRender();
    // RENDER CODE END

    if(!levelManager.GetIsLevelBuilding())
      std::cout << GetDeltaTime() << std::endl;
    FinishFrame();
  }

  return 0;
}
