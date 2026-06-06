#pragma once

#include "Hall/System.h"

enum class Button {
  B = 0,
  Y = 1,
  Select = 2,
  Start = 3,
  Up = 4,
  Down = 5,
  Left = 6,
  Right = 7,
  A = 8,
  X = 9,
  L = 10,
  R = 11
};

struct InputManager {

  static Hall::ControllerState oldState0;
  static Hall::ControllerState oldState1;

  static Hall::ControllerState state0;
  static Hall::ControllerState state1;

  static void Update();
  static bool GetButtonUp(int id, Button btn);
  static bool GetButtonDown(int id, Button btn);
  static bool GetButton(int id, Button btn);
  static bool GetAnyButtonDown(int id);
  static bool GetAnyButtonUp(int id);
};
