#pragma once

void TimeInit();
float ToSeconds(unsigned long long time);
float GetTimeSinceStartup();

void SetTargetFramerate(int framerate);
float GetTargetTimePerFrame();
void SetDeltaTime(float deltaTime);
float GetDeltaTime();