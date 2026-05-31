#include "InputManager.hpp"
#include "Hall/System.h"

Hall::ControllerState InputManager::oldState0;
Hall::ControllerState InputManager::oldState1;
Hall::ControllerState InputManager::state0;
Hall::ControllerState InputManager::state1;

bool InputManager::GetButtonUp(int id, Button btn) {
  int b = static_cast<int>(btn);
  switch (id) {
  case 0:
    return (oldState0 & (1 << b)) && !(state0 & (1 << b));
  case 1:
    return (oldState1 & (1 << b)) && !(state1 & (1 << b));
  default:
    return false;
  }
};

bool InputManager::GetButtonDown(int id, Button btn) {
  int b = static_cast<int>(btn);
  switch (id) {
  case 0:
    return !(oldState0 & (1 << b)) && (state0 & (1 << b));
  case 1:
    return !(oldState1 & (1 << b)) && (state1 & (1 << b));
  default:
    return false;
  }
}

bool InputManager::GetButton(int id, Button btn) {
  int b = static_cast<int>(btn);
  switch (id) {
  case 0:
    return (state0 & (1 << b));
  case 1:
    return (state1 & (1 << b));
  default:
    return false;
  }
}

void InputManager::Update() {
  oldState0 = state0;
  oldState1 = state1;

  state0 = Hall::GetController(0);
  state1 = Hall::GetController(1);
}
