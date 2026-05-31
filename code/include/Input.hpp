#include "Hall/System.h"

struct Input {

  Hall::ControllerState oldState0;
  Hall::ControllerState oldState1;

  Hall::ControllerState state0;
  Hall::ControllerState state1;

  virtual void Update();

  virtual bool GetA();
  virtual bool GetAUP();
  virtual bool GetADown();

  virtual bool GetB();
  virtual bool GetBUp();
  virtual bool GetBDown();
};
