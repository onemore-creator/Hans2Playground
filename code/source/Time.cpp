#include <Hall/Hall.h>
#include "Time.hpp"

static unsigned long long startTime;
static float timePerFrame;
static float deltaTime = 1 / 60.0f;

float ToSeconds(unsigned long long time)
{
    return time / (float)Hall::SYSTEM_CLK_FREQUENCY;
}

void TimeInit()
{
    startTime = Hall::GetSystemTime();
}

float GetTimeSinceStartup()
{
    unsigned long long duration = Hall::GetSystemTime() - startTime;
    return ToSeconds(duration);
}

void SetTargetFramerate(int framerate)
{
    timePerFrame = 1.0f / framerate;
#ifdef DESKTOP
    Hall::RaylibSetTargetFramerate(framerate);
#endif
}

float GetTargetTimePerFrame()
{
    return timePerFrame;
}

void SetDeltaTime(float deltaTime)
{
    ::deltaTime = deltaTime;
}

float GetDeltaTime()
{
    return deltaTime;
}