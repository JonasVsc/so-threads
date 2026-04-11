#pragma once
#include <SDL3/SDL.h>

class SpriteSheet
{
public:

    SpriteSheet(SDL_Renderer* renderer, const char* bmp_path);

    ~SpriteSheet();

    SDL_Texture* texture() { return m_texture; }

private:

    SDL_Texture* m_texture;

}; // class SpriteSheet