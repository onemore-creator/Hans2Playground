#pragma once

namespace Halib::Time
{
    void Init();
    float ToSeconds(unsigned long long time);
    float GetTimeSinceStartup();

    void SetTargetFramerate(int framerate);
    float GetTargetTimePerFrame();
    void SetDeltaTime(float deltaTime);
    float GetDeltaTime();
} // Engine