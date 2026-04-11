#pragma once

#include <SDL3/SDL.h>
#include <vector>

struct Animation
{
    std::vector<SDL_Rect> frames;
    float frame_duration;
};
